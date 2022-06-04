// Copyright Epic Games, Inc. All Rights Reserved.

#include "MaskFogPostProcess.h"
#include "FogMaskPixelShader.h"

#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "RHI.h"
#include "GlobalShader.h"
#include "RHICommandList.h"
#include "RenderGraphBuilder.h"
#include "RenderTargetPool.h"
#include "Runtime/Core/Public/Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "Runtime/Renderer/Private/PostProcess/SceneRenderTargets.h"
#include "Runtime/Renderer/Private/SceneRendering.h"

#define LOCTEXT_NAMESPACE "FMaskFogPostProcessModule"

DECLARE_GPU_STAT_NAMED(ShaderPlugin_Render, TEXT("ShaderPlugin: Root Render"));
DECLARE_GPU_STAT_NAMED(ShaderPlugin_Pixel, TEXT("ShaderPlugin: Render Pixel Shader"));

void FMaskFogPostProcessModule::StartupModule()
{
	OnPostResolvedSceneColorHandle.Reset();
	bCachedParametersValid = false;

	// Maps virtual shader source directory to the plugin's actual shaders directory.
	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("MaskFogPostProcess"))->GetBaseDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/Shaders"), PluginShaderDir);
}

void FMaskFogPostProcessModule::ShutdownModule()
{
	EndRendering();
}

void FMaskFogPostProcessModule::BeginRendering()
{
	if (OnPostResolvedSceneColorHandle.IsValid())
	{
		return;
	}
	bCachedParametersValid = false;
	const FName RendererModuleName("Renderer");
	IRendererModule* RendererModule = FModuleManager::GetModulePtr<IRendererModule>(RendererModuleName);
	if (RendererModule)
	{
		OnPostResolvedSceneColorHandle = RendererModule->GetResolvedSceneColorCallbacks().AddRaw(this, 
			&FMaskFogPostProcessModule::PostResolveSceneColor_RenderThread);
		OnPostOpaqueRenderDelegateHandle = RendererModule->RegisterPostOpaqueRenderDelegate(
			FPostOpaqueRenderDelegate::CreateRaw(this, &FMaskFogPostProcessModule::PostOpaqueRender_RenderThread));
	}
}

void FMaskFogPostProcessModule::EndRendering()
{
	if (!OnPostResolvedSceneColorHandle.IsValid())
	{
		return;
	}
	const FName RendererModuleName("Renderer");
	IRendererModule* RendererModule = FModuleManager::GetModulePtr<IRendererModule>(RendererModuleName);
	if (RendererModule)
	{
		RendererModule->GetResolvedSceneColorCallbacks().Remove(OnPostResolvedSceneColorHandle);
		RendererModule->RemovePostOpaqueRenderDelegate(OnPostOpaqueRenderDelegateHandle);
	}
	OnPostResolvedSceneColorHandle.Reset();
}

void FMaskFogPostProcessModule::UpdateParameters(FShaderFogMaskParameters& DrawParameters)
{
	FVector2D ViewSize;
	RenderEveryFrameLock.Lock();
	ViewSize = CachedFogMaskParameters.ViewSize;
	CachedFogMaskParameters = DrawParameters;
	bCachedParametersValid = true;
	RenderEveryFrameLock.Unlock();
	if (bIsGameView && !bIsSceneCapture)
		DrawParameters.ViewSize = ViewSize;
}

void FMaskFogPostProcessModule::PostResolveSceneColor_RenderThread(FRHICommandListImmediate& RHICmdList, class FSceneRenderTargets& SceneContext)
{
	if (!bCachedParametersValid || !bIsGameView)
	{
		return;
	}

	// Depending on your data, you might not have to lock here, just added this code to show how you can do it if you have to.
	RenderEveryFrameLock.Lock();
	FShaderFogMaskParameters Copy = CachedFogMaskParameters;
	const FTexture2DRHIRef& RHISceneDepth =
		(const FTexture2DRHIRef&)SceneContext.SceneDepthZ->GetRenderTargetItem().ShaderResourceTexture;
	Copy.SceneDepth = RHISceneDepth;
	RenderEveryFrameLock.Unlock();

	Draw_RenderThread(Copy);
}

void FMaskFogPostProcessModule::PostOpaqueRender_RenderThread(FPostOpaqueRenderParameters& Parameters)
{
	if (!bCachedParametersValid)
	{
		return;
	}

	// Depending on your data, you might not have to lock here, just added this code to show how you can do it if you have to.
	RenderEveryFrameLock.Lock();
	const FViewInfo* View =(FViewInfo*)Parameters.Uid;
	bIsGameView = View->bIsGameView;
	bIsSceneCapture = View->bIsSceneCapture;
	if (bIsGameView && !bIsSceneCapture)
	{
		CachedFogMaskParameters.InvDeviceZToWorldZTransform = View->InvDeviceZToWorldZTransform;
		CachedFogMaskParameters.ViewSize = Parameters.ViewportRect.Size();
	}
	RenderEveryFrameLock.Unlock();
}

void FMaskFogPostProcessModule::Draw_RenderThread(const FShaderFogMaskParameters& DrawParameters)
{
	check(IsInRenderingThread());

	if (!bIsGameView || bIsSceneCapture || !DrawParameters.RTDest || !DrawParameters.RTSrc || !DrawParameters.RTBlurTemp ||
		DrawParameters.ViewSize.X <= 0 || DrawParameters.ViewSize.Y <= 0)
	{
		return;
	}

	FRHICommandListImmediate& RHICmdList = GRHICommandList.GetImmediateCommandList();

	QUICK_SCOPE_CYCLE_COUNTER(STAT_ShaderPlugin_Render); // Used to gather CPU profiling data for the UE4 session frontend
	SCOPED_DRAW_EVENT(RHICmdList, ShaderPlugin_Render); // Used to profile GPU activity and add metadata to be consumed by for example RenderDoc

	FogMaskPixelShader::DrawToRenderTarget_RenderThread(RHICmdList, DrawParameters);
	float BlurOffsetX = FMath::Max(0.0001f, DrawParameters.BlurRadius) / DrawParameters.RTBlurTemp->SizeX;
	float BlurOffsetY = FMath::Max(0.0001f, DrawParameters.BlurRadius) / DrawParameters.RTBlurTemp->SizeY;
	//
	FogMaskPixelShader::BlurToRenderTarget_RenderThread(RHICmdList, DrawParameters.RTDest,
		DrawParameters.RTBlurTemp01, FVector2D(BlurOffsetX, 0));
	FogMaskPixelShader::BlurToRenderTarget_RenderThread(RHICmdList, DrawParameters.RTBlurTemp01,
		DrawParameters.RTBlurTemp, FVector2D(0, BlurOffsetY));
	int Iteration = FMath::Max(0, DrawParameters.Iterations);
	for (int i = 1; i < Iteration; ++i) {
		FogMaskPixelShader::BlurToRenderTarget_RenderThread(RHICmdList, DrawParameters.RTBlurTemp,
			DrawParameters.RTBlurTemp01, FVector2D(BlurOffsetX, 0));
		FogMaskPixelShader::BlurToRenderTarget_RenderThread(RHICmdList, DrawParameters.RTBlurTemp01,
			DrawParameters.RTBlurTemp, FVector2D(0, BlurOffsetY));
	}
	//combine
	FogMaskPixelShader::CombineToRenderTarget_RenderThread(RHICmdList, DrawParameters.RTDest,
		DrawParameters.RTBlurTemp, DrawParameters.RTBlurTemp01, DrawParameters.RimFactor);
	FogMaskPixelShader::CombineToRenderTarget_RenderThread(RHICmdList, DrawParameters.RTBlurTemp01,
		DrawParameters.RTBlurTemp, DrawParameters.RTDest, 0);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMaskFogPostProcessModule, MaskFogPostProcess)