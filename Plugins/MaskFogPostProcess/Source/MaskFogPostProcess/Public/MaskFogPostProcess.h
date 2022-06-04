// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#include "RenderGraphResources.h"
#include "Runtime/Engine/Classes/Engine/TextureRenderTarget2D.h"

// This struct contains all the data we need to pass from the game thread to draw our effect.
struct FShaderFogMaskParameters
{
	UTextureRenderTarget2D* RTDest;
	UTextureRenderTarget2D* RTSrc;
	UTextureRenderTarget2D* RTBlurTemp;
	UTextureRenderTarget2D* RTBlurTemp01;
	//transient
	FTextureRHIRef SceneDepth;
	FVector2D ViewSize;
	FVector4 InvDeviceZToWorldZTransform;
	float BlurRadius;
	float RimFactor;
	int Iterations;

	FIntPoint GetRenderTargetSize() const
	{
		return CachedRenderTargetSize;
	}

	FShaderFogMaskParameters() { }
	FShaderFogMaskParameters(UTextureRenderTarget2D* Src, UTextureRenderTarget2D* Temp, 
		UTextureRenderTarget2D* Temp01, UTextureRenderTarget2D* Dest)
		: RTSrc(Src)
		, RTBlurTemp(Temp)
		, RTBlurTemp01(Temp01)
		, RTDest(Dest)
	{
		CachedRenderTargetSize = RTDest ? FIntPoint(RTDest->SizeX, RTDest->SizeY) : FIntPoint::ZeroValue;
	}

private:
	FIntPoint CachedRenderTargetSize;
};

class FMaskFogPostProcessModule : public IModuleInterface
{
public:
	static inline FMaskFogPostProcessModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FMaskFogPostProcessModule>("MaskFogPostProcess");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("MaskFogPostProcess");
	}
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
public:
	// Call this when you want to hook onto the renderer and start drawing. The shader will be executed once per frame.
	void BeginRendering();

	// When you are done, call this to stop drawing.
	void EndRendering();

	// Call this whenever you have new parameters to share. You could set this up to update different sets of properties at
	// different intervals to save on locking and GPU transfer time.
	void UpdateParameters(FShaderFogMaskParameters& DrawParameters);

private:
	FShaderFogMaskParameters CachedFogMaskParameters;
	FDelegateHandle OnPostResolvedSceneColorHandle;
	FDelegateHandle OnPostOpaqueRenderDelegateHandle;
	FCriticalSection RenderEveryFrameLock;
	volatile bool bCachedParametersValid;
	volatile bool bIsGameView = false;
	volatile bool bIsSceneCapture = false;

	void PostResolveSceneColor_RenderThread(FRHICommandListImmediate& RHICmdList, class FSceneRenderTargets& SceneContext);
	void Draw_RenderThread(const FShaderFogMaskParameters& DrawParameters);
	void PostOpaqueRender_RenderThread(FPostOpaqueRenderParameters& Parameters);
};
