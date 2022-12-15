// Copyright (c) 2022 Jakub Ferliński.

#include "TransitionWidgetParent.h"

#include "LoadingScreenFunctionLibrary.h"
#include "LoadingScreenSettings.h"

UMaterialInterface* UTransitionWidgetParent::GetTransitionMaterial() const
{
	return Cast<UMaterialInterface>(GetDefault<ULoadingScreenSettings>()->TransitionMaterial.TryLoad());
}

float UTransitionWidgetParent::GetTransitionDuration() const
{
	return ULoadingScreenFunctionLibrary::GetTransitionDuration();
}

TArray<UMaterialInterface*> UTransitionWidgetParent::GetLoadingSequence() const
{
	return ULoadingScreenFunctionLibrary::GetLoadingSequence();
}

int32 UTransitionWidgetParent::GetLoadingSequenceIndex() const
{
	return ULoadingScreenFunctionLibrary::GetLoadingSequenceIndex();
}

float UTransitionWidgetParent::GetLoadingSequenceInterval()
{
	return ULoadingScreenFunctionLibrary::GetLoadingSequenceIndex();
}

void UTransitionWidgetParent::IncrementLoadingSequenceIndex(const float DeltaTime) const
{
	ULoadingScreenFunctionLibrary::IncrementLoadingSequenceIndex(DeltaTime);
}

FImageSettings UTransitionWidgetParent::GetBackgroundImage() const
{
	return ULoadingScreenFunctionLibrary::GetBackgroundImage();
}

UMaterialInterface* UTransitionWidgetParent::GetOverlayMaterial() const
{
	return ULoadingScreenFunctionLibrary::GetOverlayMaterial();
}