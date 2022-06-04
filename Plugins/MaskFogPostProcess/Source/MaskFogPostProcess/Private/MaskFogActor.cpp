// Fill out your copyright notice in the Description page of Project Settings.


#include "MaskFogActor.h"
#include "MaskFogPostProcess.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/PostProcessVolume.h"

// Sets default values
AMaskFogActor::AMaskFogActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MaskSceneCaptureComponent2D"));
	SceneCapture->SetupAttachment(RootComponent);
	
}

UTextureRenderTarget2D* AMaskFogActor::CreateRT(const TEnumAsByte<ETextureRenderTargetFormat> RenderTargetFormat)
{
	UTextureRenderTarget2D*  RT = NewObject<UTextureRenderTarget2D>(this);
	RT->ClearColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);
	RT->RenderTargetFormat = RenderTargetFormat;
	RT->InitAutoFormat(RTInitSize, RTInitSize);
	return RT;
}

void AMaskFogActor::InitRT()
{
	RTMaskBG = CreateRT(RTF_R32f);
	FinalMask = CreateRT(RTF_R8);
	RTBlurTemp01 = CreateRT(RTF_R8);
	RTBlurTemp = CreateRT(RTF_R8);
}

// Called when the game starts or when spawned
void AMaskFogActor::BeginPlay()
{
	Super::BeginPlay();
	if (SceneCapture != nullptr && PPMaterialMaskFog != nullptr && GlobalPPV != nullptr) {
		InitRT();
		SceneCapture->CaptureSource = ESceneCaptureSource::SCS_SceneDepth;
		SceneCapture->TextureTarget = RTMaskBG;
		UMaterialInstanceDynamic* MID = UMaterialInstanceDynamic::Create(PPMaterialMaskFog, this);
		MID->SetTextureParameterValue("Mask", (UTexture*)FinalMask);
		GlobalPPV->Settings.AddBlendable(MID, 1.0f);
		FMaskFogPostProcessModule::Get().BeginRendering();
	}
}

void AMaskFogActor::BeginDestroy()
{
	if (SceneCapture) {
		SceneCapture->TextureTarget = nullptr;
	}
	if (RTMaskBG) {
		RTMaskBG->ReleaseResource();
		RTMaskBG = nullptr;
	}
	if (FinalMask) {
		FinalMask->ReleaseResource();
		FinalMask = nullptr;
	}
	if (RTBlurTemp) {
		RTBlurTemp->ReleaseResource();
		RTBlurTemp = nullptr;
	}
	if (RTBlurTemp01) {
		RTBlurTemp01->ReleaseResource();
		RTBlurTemp01 = nullptr;
	}
	FMaskFogPostProcessModule::Get().EndRendering();
	Super::BeginDestroy();
}

// Called every frame
void AMaskFogActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FShaderFogMaskParameters DrawParameters(SceneCapture->TextureTarget, RTBlurTemp, RTBlurTemp01, FinalMask);
	DrawParameters.BlurRadius = BlurRadius;
	DrawParameters.RimFactor = RimFactor;
	DrawParameters.Iterations = Iterations;
	// If doing this for realsies, you should avoid doing this every frame unless you have to of course.
	// We set it every frame here since we're updating the end color and simulation state. Boop.
	FMaskFogPostProcessModule::Get().UpdateParameters(DrawParameters);
	if (RTMaskBG && DrawParameters.ViewSize.X > 0 && DrawParameters.ViewSize.Y > 0)
	{
		uint32 ResX = FMath::FloorToInt(DrawParameters.ViewSize.X * ResolutionScale);
		uint32 ResY = FMath::FloorToInt(DrawParameters.ViewSize.Y * ResolutionScale);
		if (ResX <= 0 || ResX > 4096 || ResY <= 0 || ResY > 4096)
			return;
		if (ResX != RTMaskBG->SizeX && ResY != RTMaskBG->SizeY && BlurResolutionScale > 0) {
			UE_LOG(LogTemp, Log, TEXT("Resize RT : %d, %d"), ResX, ResY);
			RTMaskBG->ResizeTarget(ResX, ResY);
			FinalMask->ResizeTarget(ResX, ResY);
			RTBlurTemp->ResizeTarget(ResX * BlurResolutionScale, ResY * BlurResolutionScale);
			RTBlurTemp01->ResizeTarget(ResX * BlurResolutionScale, ResY * BlurResolutionScale);
		}
	}
}

