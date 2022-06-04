// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MaskFogPostProcess/Public/MaskFogActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMaskFogActor() {}
// Cross Module References
	MASKFOGPOSTPROCESS_API UClass* Z_Construct_UClass_AMaskFogActor_NoRegister();
	MASKFOGPOSTPROCESS_API UClass* Z_Construct_UClass_AMaskFogActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_MaskFogPostProcess();
	ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_APostProcessVolume_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USceneCaptureComponent2D_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UTextureRenderTarget2D_NoRegister();
// End Cross Module References
	void AMaskFogActor::StaticRegisterNativesAMaskFogActor()
	{
	}
	UClass* Z_Construct_UClass_AMaskFogActor_NoRegister()
	{
		return AMaskFogActor::StaticClass();
	}
	struct Z_Construct_UClass_AMaskFogActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PPMaterialMaskFog_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_PPMaterialMaskFog;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GlobalPPV_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_GlobalPPV;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ResolutionScale_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ResolutionScale;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BlurResolutionScale_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_BlurResolutionScale;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BlurRadius_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_BlurRadius;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RimFactor_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_RimFactor;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Iterations_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Iterations;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SceneCapture_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SceneCapture;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FinalMask_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_FinalMask;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RTMaskBG_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_RTMaskBG;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RTBlurTemp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_RTBlurTemp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RTBlurTemp01_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_RTBlurTemp01;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMaskFogActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_MaskFogPostProcess,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMaskFogActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "MaskFogActor.h" },
		{ "ModuleRelativePath", "Public/MaskFogActor.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMaskFogActor_Statics::NewProp_PPMaterialMaskFog_MetaData[] = {
		{ "Category", "MaskFog" },
		{ "ModuleRelativePath", "Public/MaskFogActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMaskFogActor_Statics::NewProp_PPMaterialMaskFog = { "PPMaterialMaskFog", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMaskFogActor, PPMaterialMaskFog), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_PPMaterialMaskFog_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_PPMaterialMaskFog_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMaskFogActor_Statics::NewProp_GlobalPPV_MetaData[] = {
		{ "Category", "MaskFog" },
		{ "ModuleRelativePath", "Public/MaskFogActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMaskFogActor_Statics::NewProp_GlobalPPV = { "GlobalPPV", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMaskFogActor, GlobalPPV), Z_Construct_UClass_APostProcessVolume_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_GlobalPPV_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_GlobalPPV_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMaskFogActor_Statics::NewProp_ResolutionScale_MetaData[] = {
		{ "Category", "MaskFog" },
		{ "ModuleRelativePath", "Public/MaskFogActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMaskFogActor_Statics::NewProp_ResolutionScale = { "ResolutionScale", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMaskFogActor, ResolutionScale), METADATA_PARAMS(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_ResolutionScale_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_ResolutionScale_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMaskFogActor_Statics::NewProp_BlurResolutionScale_MetaData[] = {
		{ "Category", "MaskFog" },
		{ "ModuleRelativePath", "Public/MaskFogActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMaskFogActor_Statics::NewProp_BlurResolutionScale = { "BlurResolutionScale", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMaskFogActor, BlurResolutionScale), METADATA_PARAMS(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_BlurResolutionScale_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_BlurResolutionScale_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMaskFogActor_Statics::NewProp_BlurRadius_MetaData[] = {
		{ "Category", "MaskFog" },
		{ "ModuleRelativePath", "Public/MaskFogActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMaskFogActor_Statics::NewProp_BlurRadius = { "BlurRadius", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMaskFogActor, BlurRadius), METADATA_PARAMS(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_BlurRadius_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_BlurRadius_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMaskFogActor_Statics::NewProp_RimFactor_MetaData[] = {
		{ "Category", "MaskFog" },
		{ "ModuleRelativePath", "Public/MaskFogActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMaskFogActor_Statics::NewProp_RimFactor = { "RimFactor", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMaskFogActor, RimFactor), METADATA_PARAMS(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_RimFactor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_RimFactor_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMaskFogActor_Statics::NewProp_Iterations_MetaData[] = {
		{ "Category", "MaskFog" },
		{ "ModuleRelativePath", "Public/MaskFogActor.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_AMaskFogActor_Statics::NewProp_Iterations = { "Iterations", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMaskFogActor, Iterations), METADATA_PARAMS(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_Iterations_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_Iterations_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMaskFogActor_Statics::NewProp_SceneCapture_MetaData[] = {
		{ "Category", "MaskFog" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/MaskFogActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMaskFogActor_Statics::NewProp_SceneCapture = { "SceneCapture", nullptr, (EPropertyFlags)0x001000000008000d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMaskFogActor, SceneCapture), Z_Construct_UClass_USceneCaptureComponent2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_SceneCapture_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_SceneCapture_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMaskFogActor_Statics::NewProp_FinalMask_MetaData[] = {
		{ "ModuleRelativePath", "Public/MaskFogActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMaskFogActor_Statics::NewProp_FinalMask = { "FinalMask", nullptr, (EPropertyFlags)0x0020080000002000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMaskFogActor, FinalMask), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_FinalMask_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_FinalMask_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMaskFogActor_Statics::NewProp_RTMaskBG_MetaData[] = {
		{ "ModuleRelativePath", "Public/MaskFogActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMaskFogActor_Statics::NewProp_RTMaskBG = { "RTMaskBG", nullptr, (EPropertyFlags)0x0020080000002000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMaskFogActor, RTMaskBG), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_RTMaskBG_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_RTMaskBG_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMaskFogActor_Statics::NewProp_RTBlurTemp_MetaData[] = {
		{ "ModuleRelativePath", "Public/MaskFogActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMaskFogActor_Statics::NewProp_RTBlurTemp = { "RTBlurTemp", nullptr, (EPropertyFlags)0x0020080000002000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMaskFogActor, RTBlurTemp), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_RTBlurTemp_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_RTBlurTemp_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMaskFogActor_Statics::NewProp_RTBlurTemp01_MetaData[] = {
		{ "ModuleRelativePath", "Public/MaskFogActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMaskFogActor_Statics::NewProp_RTBlurTemp01 = { "RTBlurTemp01", nullptr, (EPropertyFlags)0x0020080000002000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMaskFogActor, RTBlurTemp01), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_RTBlurTemp01_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMaskFogActor_Statics::NewProp_RTBlurTemp01_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMaskFogActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMaskFogActor_Statics::NewProp_PPMaterialMaskFog,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMaskFogActor_Statics::NewProp_GlobalPPV,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMaskFogActor_Statics::NewProp_ResolutionScale,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMaskFogActor_Statics::NewProp_BlurResolutionScale,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMaskFogActor_Statics::NewProp_BlurRadius,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMaskFogActor_Statics::NewProp_RimFactor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMaskFogActor_Statics::NewProp_Iterations,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMaskFogActor_Statics::NewProp_SceneCapture,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMaskFogActor_Statics::NewProp_FinalMask,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMaskFogActor_Statics::NewProp_RTMaskBG,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMaskFogActor_Statics::NewProp_RTBlurTemp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMaskFogActor_Statics::NewProp_RTBlurTemp01,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMaskFogActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMaskFogActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AMaskFogActor_Statics::ClassParams = {
		&AMaskFogActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AMaskFogActor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AMaskFogActor_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AMaskFogActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AMaskFogActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AMaskFogActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AMaskFogActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AMaskFogActor, 953571469);
	template<> MASKFOGPOSTPROCESS_API UClass* StaticClass<AMaskFogActor>()
	{
		return AMaskFogActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AMaskFogActor(Z_Construct_UClass_AMaskFogActor, &AMaskFogActor::StaticClass, TEXT("/Script/MaskFogPostProcess"), TEXT("AMaskFogActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMaskFogActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
