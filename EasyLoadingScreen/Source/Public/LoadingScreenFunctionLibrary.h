// Copyright (c) 2022 Jakub Ferliński.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LoadingScreenFunctionLibrary.generated.h"

UCLASS()
class EASYLOADINGSCREEN_API ULoadingScreenFunctionLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, meta = (Tooltip = "Set Index of next displayed background image, negative value gets random entry"), Category = "Loading Screen")
	static void SetBackgroundImageIndex(const int32 NewIndex = -1);

	static float GetTransitionDuration();
	static float GetTransitionPhase();
	static void SetTransitionPhase(const float NewPhase);
	
	static enum ELoadingSequenceType GetLoadingSequenceType();
	static TArray<UMaterialInterface*> GetLoadingSequence();
	static int32 GetLoadingSequenceIndex();
	static float GetLoadingSequenceTime();
	static float GetLoadingSequenceInterval();
	static void IncrementLoadingSequenceIndex(const float DeltaTime);
	static void SkipLoadingSequenceFrame();
	static UMaterialInterface* GetAnimatedMaterial();
	
	static struct FImageSettings GetBackgroundImage();
	
	static UMaterialInterface* GetOverlayMaterial();
	static UMaterialInterface* GetTransitionMaterial();


private:
		
	static float TransitionDuration;
	static float TransitionPhase;

	static int32 BackgroundImageIndex;
	static int32 BackgroundImageArrayNum;
	
	static int32 LoadingSequenceIndex;
	static int32 LoadingSequenceArrayNum;
	static float LoadingSequenceInterval;
	static float LoadingSequenceDeltaTime;
	static float LoadingSequenceTime;
};
