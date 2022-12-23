// Copyright (c) 2022 Jakub Ferliński.

#include "TransitionWidgetParent.h"

#include "LoadingScreenFunctionLibrary.h"
#include "LoadingScreenSettings.h"

// The only reason this exists and is not static is to reduce visible nodes to the user

UMaterialInterface* UTransitionWidgetParent::GetTransitionMaterial() const
{
	return ULoadingScreenFunctionLibrary::GetTransitionMaterial();
}

float UTransitionWidgetParent::GetTransitionPhase() const
{
	return ULoadingScreenFunctionLibrary::GetTransitionPhase();
}

void UTransitionWidgetParent::SetTransitionPhase(const float NewPhase)
{
	ULoadingScreenFunctionLibrary::SetTransitionPhase(NewPhase);
}

float UTransitionWidgetParent::GetTransitionDuration() const
{
	return ULoadingScreenFunctionLibrary::GetTransitionDuration();
}

ELoadingSequenceType UTransitionWidgetParent::GetLoadingSequenceType() const
{
	return ULoadingScreenFunctionLibrary::GetLoadingSequenceType();
}

TArray<UMaterialInterface*> UTransitionWidgetParent::GetLoadingSequence() const
{
	return ULoadingScreenFunctionLibrary::GetLoadingSequence();
}

int32 UTransitionWidgetParent::GetLoadingSequenceIndex() const
{
	return ULoadingScreenFunctionLibrary::GetLoadingSequenceIndex();
}

float UTransitionWidgetParent::GetLoadingSequenceTime() const
{
	return ULoadingScreenFunctionLibrary::GetLoadingSequenceTime();
}

void UTransitionWidgetParent::IncrementLoadingSequenceIndex(const float DeltaTime) const
{
	ULoadingScreenFunctionLibrary::IncrementLoadingSequenceIndex(DeltaTime);
}

void UTransitionWidgetParent::SkipLoadingSequenceFrame() const
{
	ULoadingScreenFunctionLibrary::SkipLoadingSequenceFrame();
}

UMaterialInterface* UTransitionWidgetParent::GetAnimatedMaterial() const
{
	return ULoadingScreenFunctionLibrary::GetAnimatedMaterial();
}

FImageSettings UTransitionWidgetParent::GetBackgroundImage() const
{
	return ULoadingScreenFunctionLibrary::GetBackgroundImage();
}

UMaterialInterface* UTransitionWidgetParent::GetOverlayMaterial() const
{
	return ULoadingScreenFunctionLibrary::GetOverlayMaterial();
}