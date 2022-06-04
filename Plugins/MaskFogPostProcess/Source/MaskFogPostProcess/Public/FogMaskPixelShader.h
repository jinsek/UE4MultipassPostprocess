// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MaskFogPostProcess.h"

class FogMaskPixelShader
{
public:
	static void DrawToRenderTarget_RenderThread(FRHICommandListImmediate& RHICmdList, const FShaderFogMaskParameters& DrawParameters);
	static void BlurToRenderTarget_RenderThread(FRHICommandListImmediate& RHICmdList,
		class UTextureRenderTarget2D* RTSrc, class UTextureRenderTarget2D* RTDest, const FVector2D& BlurOffset);
	static void CombineToRenderTarget_RenderThread(FRHICommandListImmediate& RHICmdList,
		class UTextureRenderTarget2D* RTSrc, class UTextureRenderTarget2D* RTBlur, class UTextureRenderTarget2D* RTDest, const float MulFactor);
};
