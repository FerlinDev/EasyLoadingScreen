// Copyright (c) 2022 Jakub Ferliński.

#include "LoadingScreenLayout.h"

#include "LoadingScreenFunctionLibrary.h"
#include "LoadingScreenSettings.h"
#include "Slate/DeferredCleanupSlateBrush.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SScaleBox.h"

void SLoadingScreenLayout::Construct(const FArguments& InArgs)
{
	const FImageSettings BackgroundImage = ULoadingScreenFunctionLibrary::GetBackgroundImage();

	if(IsValid(BackgroundImage.Image))
	{
		ImageBrush = FDeferredCleanupSlateBrush::CreateBrush(BackgroundImage.Image);
	}

	UMaterialInterface* OverlayMaterial = ULoadingScreenFunctionLibrary::GetOverlayMaterial();
	
	if(IsValid(OverlayMaterial))
	{
		OverlayBrush = FDeferredCleanupSlateBrush::CreateBrush(OverlayMaterial, FVector2D{64,64});
	}

	const TArray<UMaterialInterface*> LoadingMaterials = ULoadingScreenFunctionLibrary::GetLoadingSequence();
	
	if (LoadingMaterials.Num() != 0)
	{	
		LoadingSequence.Empty();
		
		for (UMaterialInterface* Material : LoadingMaterials)
		{
			LoadingSequence.Add(FDeferredCleanupSlateBrush::CreateBrush(Material, FVector2D{64,64}));	
		}
		
		LoadingIcon = SNew(SImage).Image(LoadingSequence[ULoadingScreenFunctionLibrary::GetLoadingSequenceIndex()]->GetSlateBrush());
	}

	ChildSlot
	[
		SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SScaleBox)
				.Stretch(EStretch::ScaleToFill)
				.StretchDirection(EStretchDirection::Both)
				.HAlign(BackgroundImage.HorizontalAlignment)
				.VAlign(BackgroundImage.VerticalAlignment)
				[
					SNew(SImage).Image(ImageBrush.IsValid() ? ImageBrush->GetSlateBrush() : nullptr)						
				]
			]	
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage).Image(OverlayBrush.IsValid() ? OverlayBrush->GetSlateBrush() : nullptr)	
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				LoadingIcon
			]
	];
}

int32 SLoadingScreenLayout::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	if (LoadingSequence.Num() > 1)
	{
		ULoadingScreenFunctionLibrary::IncrementLoadingSequenceIndex(Args.GetDeltaTime());
		StaticCastSharedRef<SImage>(LoadingIcon)->SetImage(LoadingSequence[ULoadingScreenFunctionLibrary::GetLoadingSequenceIndex()]->GetSlateBrush());
	}
	
	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
}