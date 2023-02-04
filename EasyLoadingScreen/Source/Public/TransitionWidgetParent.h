// Copyright (c) 2022 Jakub Ferliński.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "TransitionWidgetParent.generated.h"

UCLASS(Abstract, HideDropdown)
class EASYLOADINGSCREEN_API UTransitionWidgetParent : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateLoadingSequence();

	UFUNCTION(BlueprintImplementableEvent)
	UMaterialInterface* GetDefaultTransitionMaterial() const;
	
	UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn))
	bool bFadeIn = false;
	
	UPROPERTY(BlueprintReadOnly)
	bool bFinishedTransition = false;
	
private:
	
	int SkippedFrames = 0;
	float SkippedTime = 0.0f;

	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* BackgroundLayer;

	UPROPERTY(meta=(BindWidget))
	class UImage* TransitionLayer;

	UPROPERTY(meta=(BindWidget))
	class UImage* BackgroundImage;

	UPROPERTY(meta=(BindWidget))
	class UImage* OverlayMaterial;

	UPROPERTY(meta=(BindWidget))
	class UImage* LoadingIcon;

	UPROPERTY()
	UMaterialInstanceDynamic* TransitionMaterial = nullptr;

	UPROPERTY()
	UMaterialInstanceDynamic* AnimatedLoadingMaterial = nullptr;

	UPROPERTY()
	TArray<UMaterialInterface*> LoadingImages;
};
