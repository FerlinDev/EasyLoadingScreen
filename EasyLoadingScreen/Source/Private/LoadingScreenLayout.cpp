// Copyright (c) 2022 Jakub Ferliński.

#include "LoadingScreenLayout.h"

#include "LoadingScreenFunctionLibrary.h"
#include "LoadingScreenSettings.h"
#include "Slate/DeferredCleanupSlateBrush.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SScaleBox.h"

void SLoadingScreenLayout::Construct(const FArguments& InArgs)
{
	SetUpLoadingIcon();
	UMaterialInterface* OverlayMaterial = ULoadingScreenFunctionLibrary::GetOverlayMaterial();
	const FImageSettings LoadingImage = ULoadingScreenFunctionLibrary::GetBackgroundImage();

	if(IsValid(LoadingImage.Image))
	{
		ImageBrush = FDeferredCleanupSlateBrush::CreateBrush(LoadingImage.Image);
	}
	
	if(IsValid(OverlayMaterial))
	{
		OverlayBrush = FDeferredCleanupSlateBrush::CreateBrush(OverlayMaterial, FVector2D{64,64});
	}

	ChildSlot
	[
		SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(0.0f)
				.BorderImage(FCoreStyle::Get().GetBrush("BlackBrush"))
				[
					SNew(SScaleBox)
					.Stretch(EStretch::ScaleToFill)
					.StretchDirection(EStretchDirection::Both)
					.HAlign(LoadingImage.HorizontalAlignment)
					.VAlign(LoadingImage.VerticalAlignment)
					[
						SNew(SImage)
						.Image(ImageBrush.IsValid() ? ImageBrush->GetSlateBrush() : nullptr)						
					]
				]
			]	
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)						
				.Image(OverlayBrush.IsValid() ? OverlayBrush->GetSlateBrush() : nullptr)	
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
	ULoadingScreenFunctionLibrary::IncrementLoadingSequenceIndex(Args.GetDeltaTime());
	
	if (CleanupBrushList.Num() > 1 && CurrentIndex != ULoadingScreenFunctionLibrary::GetLoadingSequenceIndex())
	{
		CurrentIndex = ULoadingScreenFunctionLibrary::GetLoadingSequenceIndex();
		StaticCastSharedRef<SImage>(LoadingIcon)->SetImage(CleanupBrushList[CurrentIndex].IsValid() ? CleanupBrushList[CurrentIndex]->GetSlateBrush() : nullptr);
	}
	
	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
}

void SLoadingScreenLayout::SetUpLoadingIcon()
{
	const TArray<UMaterialInterface*> Materials = ULoadingScreenFunctionLibrary::GetLoadingSequence();
	
	if (Materials.Num() == 0)
	{
		return;
	}
	
	CleanupBrushList.Empty();
		
	for (UMaterialInterface* Material : Materials)
	{
		CleanupBrushList.Add(FDeferredCleanupSlateBrush::CreateBrush(Material, FVector2D{64,64}));	
	}
		
	LoadingIcon = SNew(SImage).Image(CleanupBrushList[ULoadingScreenFunctionLibrary::GetLoadingSequenceIndex()]->GetSlateBrush());
}
