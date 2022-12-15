// Copyright (c) 2022 Jakub Ferliński.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TransitionWidgetParent.generated.h"

UCLASS()
class EASYLOADINGSCREEN_API UTransitionWidgetParent : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Loading Screen")
	UMaterialInterface* GetTransitionMaterial() const;

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Loading Screen")
	float GetTransitionDuration() const;
	
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Loading Screen")
	TArray<UMaterialInterface*> GetLoadingSequence() const;
	
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Loading Screen")
	int32 GetLoadingSequenceIndex() const;

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Loading Screen")
	float GetLoadingSequenceInterval();
	
	UFUNCTION( BlueprintCallable, Category = "Loading Screen")
	void IncrementLoadingSequenceIndex(const float DeltaTime) const;

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Loading Screen")
	struct FImageSettings GetBackgroundImage() const; 

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Loading Screen")
	UMaterialInterface* GetOverlayMaterial() const;
};