// Copyright (c) 2022 Jakub Ferliński.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "LoadingScreenSettings.generated.h"

UENUM(BlueprintType)
enum ELoadingSequenceType
{
	FrameAnimation,
	AnimatedMaterial
};

USTRUCT(BlueprintType)
struct FImageSettings
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UTexture2D* Image = nullptr;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TEnumAsByte<EVerticalAlignment> VerticalAlignment = EVerticalAlignment::VAlign_Center;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TEnumAsByte<EHorizontalAlignment> HorizontalAlignment = EHorizontalAlignment::HAlign_Center;
};

UCLASS(Config = "Game", defaultconfig, meta = (DisplayName = "Easy Loading Screen"))
class EASYLOADINGSCREEN_API ULoadingScreenSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	ULoadingScreenSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer){};
	
	UPROPERTY(Config, EditAnywhere, Category = "Transition", meta = (UIMin = 0.00, ClampMin = "0"))
	float TransitionDuration = 1.0f;

	UPROPERTY(Config, EditAnywhere, Category = "Transition", meta = (AllowedClasses = "Material , MaterialInstance"))
	FSoftObjectPath TransitionMaterial;
	
	UPROPERTY(Config, EditAnywhere, Category = "Background", meta = (AllowedClasses = "Material , MaterialInstance"))
	FSoftObjectPath OverlayMaterial;

	UPROPERTY(Config, EditAnywhere, Category = "Background")
	TArray<FImageSettings> BackgroundImages;
	
	UPROPERTY(Config, EditAnywhere, Category = "Loading Sequence")
    TEnumAsByte<ELoadingSequenceType> SequenceType = ELoadingSequenceType::FrameAnimation;

	UPROPERTY(Config, EditAnywhere, Category = "Loading Sequence", meta = (ClampMin = "1", EditCondition ="SequenceType==ELoadingSequenceType::FrameAnimation", EditConditionHides))
	int Framerate = 24;
	
	UPROPERTY(Config, EditAnywhere, DisplayName = "Loading Sequence", Category = "Loading Sequence", meta = (AllowedClasses = "Material , MaterialInstance", EditCondition ="SequenceType==ELoadingSequenceType::FrameAnimation", EditConditionHides))
	TArray<FSoftObjectPath> LoadingMaterials;

	UPROPERTY(Config, EditAnywhere, DisplayName = "Loading Sequence", Category = "Loading Sequence", meta = (AllowedClasses = "Material , MaterialInstance", EditCondition ="SequenceType==ELoadingSequenceType::AnimatedMaterial", EditConditionHides))
	FSoftObjectPath AnimatedMaterial;
};