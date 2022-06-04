// Fill out your copyright notice in the Description page of Project Settings.


#include "FogMaskPixelShader.h"

#include "ShaderParameterUtils.h"
#include "RHIStaticStates.h"
#include "Shader.h"
#include "GlobalShader.h"
#include "RenderGraphBuilder.h"
#include "RenderGraphUtils.h"
#include "ShaderParameterMacros.h"
#include "ShaderParameterStruct.h"
#include "UniformBuffer.h"
#include "RHICommandList.h"
#include "Containers/DynamicRHIResourceArray.h"
#include "Runtime/RenderCore/Public/PixelShaderUtils.h"

/************************************************************************/
/* Simple static vertex buffer.                                         */
/************************************************************************/
class FSimpleScreenVertexBuffer : public FVertexBuffer
{
public:
	/** Initialize the RHI for this rendering resource */
	void InitRHI()
	{
		TResourceArray<FFilterVertex, VERTEXBUFFER_ALIGNMENT> Vertices;
		Vertices.SetNumUninitialized(6);

		Vertices[0].Position = FVector4(-1, 1, 0, 1);
		Vertices[0].UV = FVector2D(0, 0);

		Vertices[1].Position = FVector4(1, 1, 0, 1);
		Vertices[1].UV = FVector2D(1, 0);

		Vertices[2].Position = FVector4(-1, -1, 0, 1);
		Vertices[2].UV = FVector2D(0, 1);

		Vertices[3].Position = FVector4(1, -1, 0, 1);
		Vertices[3].UV = FVector2D(1, 1);

		// Create vertex buffer. Fill buffer with initial data upon creation
		FRHIResourceCreateInfo CreateInfo(&Vertices);
		VertexBufferRHI = RHICreateVertexBuffer(Vertices.GetResourceDataSize(), BUF_Static, CreateInfo);
	}
};
TGlobalResource<FSimpleScreenVertexBuffer> GSimpleScreenVertexBuffer;

/************************************************************************/
/* A simple passthrough vertexshader that we will use.                  */
/************************************************************************/
class FSimplePassThroughVS : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FSimplePassThroughVS);

public:
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return true;
	}

	FSimplePassThroughVS() { }
	FSimplePassThroughVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FGlobalShader(Initializer) { }
};

/**********************************************************************************************/
/* This class carries our parameter declarations and acts as the bridge between cpp and HLSL. */
/**********************************************************************************************/
class FFogMaskPixelShaderPS : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FFogMaskPixelShaderPS);
	SHADER_USE_PARAMETER_STRUCT(FFogMaskPixelShaderPS, FGlobalShader);

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_TEXTURE(Texture2D, SrcRT)
		SHADER_PARAMETER_SAMPLER(SamplerState, SrcRTSampler)
		SHADER_PARAMETER_TEXTURE(Texture2D, SceneDepthTexture)
		SHADER_PARAMETER_SAMPLER(SamplerState, SceneDepthSampler)
		SHADER_PARAMETER(FVector2D, TextureSize) // Metal doesn't support GetDimensions(), so we send in this data via our parameters.
		SHADER_PARAMETER(FVector4, InvDeviceZToWorldZTransform)
		SHADER_PARAMETER(FVector2D, ScreenUVSize)		
		END_SHADER_PARAMETER_STRUCT()

public:
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}
};

// This will tell the engine to create the shader and where the shader entry point is.
//                           ShaderType                            ShaderPath                Shader function name    Type
IMPLEMENT_GLOBAL_SHADER(FSimplePassThroughVS, "/Shaders/FogMaskPixelShader.usf", "MainVertexShader", SF_Vertex);
IMPLEMENT_GLOBAL_SHADER(FFogMaskPixelShaderPS, "/Shaders/FogMaskPixelShader.usf", "MainPixelShader", SF_Pixel);

void FogMaskPixelShader::DrawToRenderTarget_RenderThread(FRHICommandListImmediate& RHICmdList, const FShaderFogMaskParameters& DrawParameters)
{
	QUICK_SCOPE_CYCLE_COUNTER(STAT_ShaderPlugin_PixelShader); // Used to gather CPU profiling data for the UE4 session frontend
	SCOPED_DRAW_EVENT(RHICmdList, ShaderPlugin_Pixel); // Used to profile GPU activity and add metadata to be consumed by for example RenderDoc

	FRHIRenderPassInfo RenderPassInfo(DrawParameters.RTDest->GetRenderTargetResource()->GetRenderTargetTexture(), ERenderTargetActions::Clear_Store);
	RHICmdList.BeginRenderPass(RenderPassInfo, TEXT("ShaderPlugin_OutputToRenderTarget"));

	auto ShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);
	TShaderMapRef<FSimplePassThroughVS> VertexShader(ShaderMap);
	TShaderMapRef<FFogMaskPixelShaderPS> PixelShader(ShaderMap);

	// Set the graphic pipeline state.
	FGraphicsPipelineStateInitializer GraphicsPSOInit;
	RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
	GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
	GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
	GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
	GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GFilterVertexDeclaration.VertexDeclarationRHI;
	GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
	GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
	GraphicsPSOInit.PrimitiveType = PT_TriangleStrip;
	SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit);

	// Setup the pixel shader
	FFogMaskPixelShaderPS::FParameters PassParameters;
	PassParameters.SrcRT = DrawParameters.RTSrc->GetRenderTargetResource()->GetRenderTargetTexture();
	PassParameters.SrcRTSampler = TStaticSamplerState<>::GetRHI();
	PassParameters.SceneDepthTexture = DrawParameters.SceneDepth;
	PassParameters.SceneDepthSampler = TStaticSamplerState<>::GetRHI();
	PassParameters.TextureSize = FVector2D(DrawParameters.GetRenderTargetSize().X, DrawParameters.GetRenderTargetSize().Y);
	PassParameters.InvDeviceZToWorldZTransform = DrawParameters.InvDeviceZToWorldZTransform;
	PassParameters.ScreenUVSize = FVector2D(DrawParameters.ViewSize.X / DrawParameters.SceneDepth->GetSizeXYZ().X,
		DrawParameters.ViewSize.Y / DrawParameters.SceneDepth->GetSizeXYZ().Y);
	SetShaderParameters(RHICmdList, PixelShader, PixelShader.GetPixelShader(), PassParameters);

	// Draw
	RHICmdList.SetStreamSource(0, GSimpleScreenVertexBuffer.VertexBufferRHI, 0);
	RHICmdList.DrawPrimitive(0, 2, 1);

	RHICmdList.EndRenderPass();
}


/**********************************************************************************************/
/* This class carries our parameter declarations and acts as the bridge between cpp and HLSL. */
/**********************************************************************************************/
class FGaussianBlurPixelShaderPS : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FGaussianBlurPixelShaderPS);
	SHADER_USE_PARAMETER_STRUCT(FGaussianBlurPixelShaderPS, FGlobalShader);

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_TEXTURE(Texture2D, SrcRT)
		SHADER_PARAMETER_SAMPLER(SamplerState, SrcRTSampler)
		SHADER_PARAMETER(FVector2D, BlurOffset)
		END_SHADER_PARAMETER_STRUCT()

public:
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}
};

// This will tell the engine to create the shader and where the shader entry point is.
//                           ShaderType                            ShaderPath                Shader function name    Type
IMPLEMENT_GLOBAL_SHADER(FGaussianBlurPixelShaderPS, "/Shaders/GaussianBlurPixelShader.usf", "MainPixelShader", SF_Pixel);

void FogMaskPixelShader::BlurToRenderTarget_RenderThread(FRHICommandListImmediate& RHICmdList,
	UTextureRenderTarget2D* RTSrc, UTextureRenderTarget2D* RTDest, const FVector2D& BlurOffset)
{
	QUICK_SCOPE_CYCLE_COUNTER(STAT_ShaderPlugin_PixelShader); // Used to gather CPU profiling data for the UE4 session frontend
	SCOPED_DRAW_EVENT(RHICmdList, ShaderPlugin_Pixel); // Used to profile GPU activity and add metadata to be consumed by for example RenderDoc

	FRHIRenderPassInfo RenderPassInfo(RTDest->GetRenderTargetResource()->GetRenderTargetTexture(), ERenderTargetActions::Clear_Store);
	RHICmdList.BeginRenderPass(RenderPassInfo, TEXT("ShaderPlugin_OutputToRenderTarget"));

	auto ShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);
	TShaderMapRef<FSimplePassThroughVS> VertexShader(ShaderMap);
	TShaderMapRef<FGaussianBlurPixelShaderPS> PixelShader(ShaderMap);

	// Set the graphic pipeline state.
	FGraphicsPipelineStateInitializer GraphicsPSOInit;
	RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
	GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
	GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
	GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
	GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GFilterVertexDeclaration.VertexDeclarationRHI;
	GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
	GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
	GraphicsPSOInit.PrimitiveType = PT_TriangleStrip;
	SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit);

	// Setup the pixel shader
	FGaussianBlurPixelShaderPS::FParameters PassParameters;
	PassParameters.SrcRT = RTSrc->GetRenderTargetResource()->GetRenderTargetTexture();
	PassParameters.SrcRTSampler = TStaticSamplerState<>::GetRHI();
	PassParameters.BlurOffset = BlurOffset;

	SetShaderParameters(RHICmdList, PixelShader, PixelShader.GetPixelShader(), PassParameters);

	// Draw
	RHICmdList.SetStreamSource(0, GSimpleScreenVertexBuffer.VertexBufferRHI, 0);
	RHICmdList.DrawPrimitive(0, 2, 1);

	RHICmdList.EndRenderPass();
}

class FFinalCombinePixelShaderPS : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FFinalCombinePixelShaderPS);
	SHADER_USE_PARAMETER_STRUCT(FFinalCombinePixelShaderPS, FGlobalShader);

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_TEXTURE(Texture2D, MaskRT)
		SHADER_PARAMETER_SAMPLER(SamplerState, MaskRTSampler)
		SHADER_PARAMETER_TEXTURE(Texture2D, BlurRT)
		SHADER_PARAMETER_SAMPLER(SamplerState, BlurRTSampler)
		SHADER_PARAMETER(float, MulFactor)
		END_SHADER_PARAMETER_STRUCT()

public:
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}
};

// This will tell the engine to create the shader and where the shader entry point is.
//                           ShaderType                            ShaderPath                Shader function name    Type
IMPLEMENT_GLOBAL_SHADER(FFinalCombinePixelShaderPS, "/Shaders/GaussianBlurPixelShader.usf", "CombinePixelShader", SF_Pixel);

void FogMaskPixelShader::CombineToRenderTarget_RenderThread(FRHICommandListImmediate& RHICmdList,
	UTextureRenderTarget2D* RTSrc, UTextureRenderTarget2D* RTBlur, UTextureRenderTarget2D* RTDest, const float MulFactor)
{
	QUICK_SCOPE_CYCLE_COUNTER(STAT_ShaderPlugin_PixelShader); // Used to gather CPU profiling data for the UE4 session frontend
	SCOPED_DRAW_EVENT(RHICmdList, ShaderPlugin_Pixel); // Used to profile GPU activity and add metadata to be consumed by for example RenderDoc

	FRHIRenderPassInfo RenderPassInfo(RTDest->GetRenderTargetResource()->GetRenderTargetTexture(), ERenderTargetActions::Clear_Store);
	RHICmdList.BeginRenderPass(RenderPassInfo, TEXT("ShaderPlugin_OutputToRenderTarget"));

	auto ShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);
	TShaderMapRef<FSimplePassThroughVS> VertexShader(ShaderMap);
	TShaderMapRef<FFinalCombinePixelShaderPS> PixelShader(ShaderMap);

	// Set the graphic pipeline state.
	FGraphicsPipelineStateInitializer GraphicsPSOInit;
	RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
	GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
	GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
	GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
	GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GFilterVertexDeclaration.VertexDeclarationRHI;
	GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
	GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
	GraphicsPSOInit.PrimitiveType = PT_TriangleStrip;
	SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit);

	// Setup the pixel shader
	FFinalCombinePixelShaderPS::FParameters PassParameters;
	PassParameters.MaskRT = RTSrc->GetRenderTargetResource()->GetRenderTargetTexture();
	PassParameters.MaskRTSampler = TStaticSamplerState<>::GetRHI();
	PassParameters.BlurRT = RTBlur->GetRenderTargetResource()->GetRenderTargetTexture();
	PassParameters.BlurRTSampler = TStaticSamplerState<>::GetRHI();
	PassParameters.MulFactor = MulFactor;

	SetShaderParameters(RHICmdList, PixelShader, PixelShader.GetPixelShader(), PassParameters);

	// Draw
	RHICmdList.SetStreamSource(0, GSimpleScreenVertexBuffer.VertexBufferRHI, 0);
	RHICmdList.DrawPrimitive(0, 2, 1);

	RHICmdList.EndRenderPass();
}