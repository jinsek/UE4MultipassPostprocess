// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TextureRenderTarget2D.h"
#include "MaskFogActor.generated.h"

UCLASS()
class MASKFOGPOSTPROCESS_API AMaskFogActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaskFogActor();
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaskFog")
		class UMaterialInterface* PPMaterialMaskFog;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaskFog")
		class APostProcessVolume* GlobalPPV;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaskFog")
		float ResolutionScale = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaskFog")
		float BlurResolutionScale = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaskFog")
		float BlurRadius = 8.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaskFog")
		float RimFactor = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaskFog")
		int32 Iterations = 5;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaskFog")
		class USceneCaptureComponent2D* SceneCapture;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	void InitRT();
	UTextureRenderTarget2D* CreateRT(const TEnumAsByte<ETextureRenderTargetFormat> RenderTargetFormat);

	UPROPERTY(transient)
		UTextureRenderTarget2D* FinalMask = nullptr;	
	UPROPERTY(transient)
		UTextureRenderTarget2D* RTMaskBG = nullptr;
	UPROPERTY(transient)
		UTextureRenderTarget2D* RTBlurTemp = nullptr;
	UPROPERTY(transient)
		UTextureRenderTarget2D* RTBlurTemp01 = nullptr;
	uint32 RTInitSize = 512;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
