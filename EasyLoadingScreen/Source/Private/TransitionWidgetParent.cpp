// Copyright (c) 2022 Jakub Ferliński.

#include "TransitionWidgetParent.h"

#include "LoadingScreenFunctionLibrary.h"
#include "LoadingScreenSettings.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Image.h"
#include "Components/ScaleBoxSlot.h"

constexpr int FramesToSkip = 5; // delay before fade out starts expressed in both time and frames
constexpr float TimeToSkip = 0.1f; // both need to pass before fade out animation starts

void UTransitionWidgetParent::NativeConstruct()
{
	Super::NativeConstruct();
	
	if(ULoadingScreenFunctionLibrary::GetTransitionDuration() <= 0.0f)
	{
		TransitionLayer->SetRenderOpacity(0.0f);
		BackgroundLayer->SetRenderOpacity(0.0f);
		bFinishedTransition = true;
		return;
	}

	BackgroundLayer->SetRenderOpacity(bFadeIn ? 0.0f : 1.0f);

	if(ULoadingScreenFunctionLibrary::GetLoadingSequenceType() == ELoadingSequenceType::FrameAnimation)
	{
		ULoadingScreenFunctionLibrary::SkipLoadingSequenceFrame();
	}
	
	const bool UseDefaultMaterial = !IsValid(ULoadingScreenFunctionLibrary::GetTransitionMaterial());
	
	TransitionMaterial = UMaterialInstanceDynamic::Create(UseDefaultMaterial ? GetDefaultTransitionMaterial() : ULoadingScreenFunctionLibrary::GetTransitionMaterial(), this);
	TransitionLayer->SetBrushFromMaterial(TransitionMaterial);
	TransitionMaterial->SetScalarParameterValue(TEXT("TransitionPhase"), ULoadingScreenFunctionLibrary::GetTransitionPhase());
	
	const FImageSettings ImageSettings = ULoadingScreenFunctionLibrary::GetBackgroundImage();

	if(IsValid(ImageSettings.Image))
	{
		BackgroundImage->SetBrushFromTexture(ImageSettings.Image);
	}
	else
	{
		BackgroundImage->SetBrushTintColor(FSlateColor(FLinearColor(0,0,0)));
	}

	UWidgetLayoutLibrary::SlotAsScaleBoxSlot(BackgroundImage)->SetHorizontalAlignment(ImageSettings.HorizontalAlignment);
	UWidgetLayoutLibrary::SlotAsScaleBoxSlot(BackgroundImage)->SetVerticalAlignment(ImageSettings.VerticalAlignment);
	
	OverlayMaterial->SetBrushFromMaterial(ULoadingScreenFunctionLibrary::GetOverlayMaterial());
	
	switch(ULoadingScreenFunctionLibrary::GetLoadingSequenceType())
	{
		case ELoadingSequenceType::FrameAnimation:
			
			LoadingImages = ULoadingScreenFunctionLibrary::GetLoadingSequence();
		
		break;
		
		case ELoadingSequenceType::AnimatedMaterial:
			
			if(IsValid(ULoadingScreenFunctionLibrary::GetAnimatedMaterial()))
			{
				AnimatedLoadingMaterial = UMaterialInstanceDynamic::Create(ULoadingScreenFunctionLibrary::GetAnimatedMaterial(), this);
				LoadingIcon->SetBrushFromMaterial(AnimatedLoadingMaterial);
			}
			else
			{
				LoadingIcon->SetRenderOpacity(0.0f);
			}
		
		break;
	}
	
	UpdateLoadingSequence();
	
}

void UTransitionWidgetParent::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(ULoadingScreenFunctionLibrary::GetTransitionDuration() <= 0.0f)
	{
		bFinishedTransition = true;
		return;
	}

	ULoadingScreenFunctionLibrary::IncrementLoadingSequenceIndex(InDeltaTime);
	UpdateLoadingSequence();

	SkippedFrames++;
	SkippedTime += InDeltaTime;

	if(bFadeIn)
	{
		const float NewTransitionPhase = ULoadingScreenFunctionLibrary::GetTransitionPhase() + (InDeltaTime / ULoadingScreenFunctionLibrary::GetTransitionDuration());
		ULoadingScreenFunctionLibrary::SetTransitionPhase(NewTransitionPhase);
		
		TransitionMaterial->SetScalarParameterValue(TEXT("TransitionPhase"), ULoadingScreenFunctionLibrary::GetTransitionPhase());
		
		if(ULoadingScreenFunctionLibrary::GetTransitionPhase() >= 1.0f)
		{
			bFinishedTransition = true;
		}
	}
	else if(SkippedFrames >= FramesToSkip && SkippedTime >= TimeToSkip)
	{
		const float NewTransitionPhase = ULoadingScreenFunctionLibrary::GetTransitionPhase() - (InDeltaTime / ULoadingScreenFunctionLibrary::GetTransitionDuration());

		ULoadingScreenFunctionLibrary::SetTransitionPhase(BackgroundLayer->GetRenderOpacity() >= 0.5 ? FMath::Clamp(NewTransitionPhase,1.0f, 2.0f) : NewTransitionPhase);

		TransitionMaterial->SetScalarParameterValue(TEXT("TransitionPhase"), ULoadingScreenFunctionLibrary::GetTransitionPhase());

		if(NewTransitionPhase <= 1.0f)
		{
			BackgroundLayer->SetRenderOpacity(0.0f);
			
			if(NewTransitionPhase <= 0.0f)
			{
				bFinishedTransition = true;
			}
		}
	}
}

void UTransitionWidgetParent::UpdateLoadingSequence()
{
	switch(ULoadingScreenFunctionLibrary::GetLoadingSequenceType())
	{
		case ELoadingSequenceType::FrameAnimation:
			
			if(LoadingImages.IsValidIndex(ULoadingScreenFunctionLibrary::GetLoadingSequenceIndex()))
			{
				LoadingIcon->SetBrushFromMaterial(LoadingImages[ULoadingScreenFunctionLibrary::GetLoadingSequenceIndex()]);
			}
		
		break;
		
		case ELoadingSequenceType::AnimatedMaterial:
			
			if(IsValid(AnimatedLoadingMaterial))
			{
				AnimatedLoadingMaterial->SetScalarParameterValue(TEXT("Time"), ULoadingScreenFunctionLibrary::GetLoadingSequenceTime());
			}
		
		break;
	}
}