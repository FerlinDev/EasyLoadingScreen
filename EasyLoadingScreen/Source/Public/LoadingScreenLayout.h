// Copyright (c) 2022 Jakub Ferliński.

#pragma once

#include "Widgets/SCompoundWidget.h"

class SLoadingScreenLayout final : public SCompoundWidget
{

public:
	SLATE_BEGIN_ARGS(SLoadingScreenLayout) {}

	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

private:
	
	TSharedPtr<class FDeferredCleanupSlateBrush> OverlayBrush;
	TSharedPtr<class FDeferredCleanupSlateBrush> ImageBrush;

	TSharedRef<SWidget> LoadingIcon = SNullWidget::NullWidget;
	TSharedPtr<class FDeferredCleanupSlateBrush> AnimatedMaterialBrush;
	TArray<TSharedPtr<class FDeferredCleanupSlateBrush>> LoadingSequence;

	TSharedPtr<class FDeferredCleanupSlateBrush> TransitionBrush;
	
	UMaterialInstanceDynamic* AnimatedMaterial = nullptr;
	bool bIsValidMaterial = false;

	UMaterialInstanceDynamic* TransitionMaterial = nullptr;
	bool bIsTransitionValid = false;
};
