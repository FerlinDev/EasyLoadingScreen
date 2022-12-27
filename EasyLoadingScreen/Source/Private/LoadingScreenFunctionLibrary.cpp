// Copyright (c) 2022 Jakub Ferliński.

#include "LoadingScreenFunctionLibrary.h"

#include "LoadingScreenSettings.h"

float ULoadingScreenFunctionLibrary::TransitionDuration = -1;
float ULoadingScreenFunctionLibrary::TransitionPhase = 0.0f;

int32 ULoadingScreenFunctionLibrary::BackgroundImageIndex = -1;
int32 ULoadingScreenFunctionLibrary::BackgroundImageArrayNum = -1;

int32 ULoadingScreenFunctionLibrary::LoadingSequenceIndex = 0;
int32 ULoadingScreenFunctionLibrary::LoadingSequenceArrayNum = -1;
float ULoadingScreenFunctionLibrary::LoadingSequenceInterval = -1;
float ULoadingScreenFunctionLibrary::LoadingSequenceDeltaTime = 0.0f;
float ULoadingScreenFunctionLibrary::LoadingSequenceTime = 0.0f;

void ULoadingScreenFunctionLibrary::SetBackgroundImageIndex(const int32 NewIndex)
{
	if(BackgroundImageArrayNum < 0)
	{
		BackgroundImageArrayNum = GetDefault<ULoadingScreenSettings>()->BackgroundImages.Num();
	}

	BackgroundImageIndex = NewIndex < 0 ? FMath::RandRange(0, BackgroundImageArrayNum - 1) : NewIndex % BackgroundImageArrayNum;
	LoadingSequenceTime = 0.0f;
	TransitionPhase = 0.0f;

	ensureMsgf(NewIndex < BackgroundImageArrayNum, TEXT("SetLoadingImageIndex -> INDEX TOO BIG"));
}

float ULoadingScreenFunctionLibrary::GetTransitionDuration()
{
	if(TransitionDuration < 0)
	{
		TransitionDuration = GetDefault<ULoadingScreenSettings>()->TransitionDuration;
	}
	return TransitionDuration;
}

float ULoadingScreenFunctionLibrary::GetTransitionPhase()
{
	return TransitionPhase;
}

void ULoadingScreenFunctionLibrary::SetTransitionPhase(const float NewPhase)
{
	TransitionPhase = FMath::Clamp(NewPhase, 0,2);
}

ELoadingSequenceType ULoadingScreenFunctionLibrary::GetLoadingSequenceType()
{
	return GetDefault<ULoadingScreenSettings>()->SequenceType;
}

TArray<UMaterialInterface*> ULoadingScreenFunctionLibrary::GetLoadingSequence()
{
	const TArray<FSoftObjectPath> MaterialPaths = GetDefault<ULoadingScreenSettings>()->LoadingMaterials;
	TArray<UMaterialInterface*> CachedMaterials;
	CachedMaterials.Reserve(MaterialPaths.Num());

	for(const FSoftObjectPath MaterialPath : MaterialPaths)
	{
		if(UMaterialInterface* SequenceMaterial = Cast<UMaterialInterface>(MaterialPath.TryLoad()))
		{
			CachedMaterials.Add(SequenceMaterial);
		}
	}
	
	if(CachedMaterials.Num() == 0)
	{
		const FSoftObjectPath TransparentAssetPath("Material'/EasyLoadingScreen/ExampleMaterials/M_FullyTransparent.M_FullyTransparent'");
		
		if(const auto TransparentMaterial = Cast<UMaterialInterface>(TransparentAssetPath.TryLoad()))
		{
			CachedMaterials.Add(TransparentMaterial);
		}
	}
	
	return CachedMaterials;
}

int32 ULoadingScreenFunctionLibrary::GetLoadingSequenceIndex()
{
	return LoadingSequenceIndex;
}

float ULoadingScreenFunctionLibrary::GetLoadingSequenceTime()
{
	return LoadingSequenceTime;
}

float ULoadingScreenFunctionLibrary::GetLoadingSequenceInterval()
{
	if(LoadingSequenceInterval < 0)
	{
		LoadingSequenceInterval = 1.0f / GetDefault<ULoadingScreenSettings>()->Framerate;
	}
	return LoadingSequenceInterval;
}

void ULoadingScreenFunctionLibrary::IncrementLoadingSequenceIndex(const float DeltaTime)
{
	LoadingSequenceTime = LoadingSequenceTime + DeltaTime;
	
	if(LoadingSequenceArrayNum < 0)
	{
		LoadingSequenceArrayNum = GetLoadingSequence().Num();
	}
	
	const float AnimInterval = GetLoadingSequenceInterval();
	LoadingSequenceDeltaTime += DeltaTime;

	if(LoadingSequenceDeltaTime >= AnimInterval)
	{
		LoadingSequenceDeltaTime = fmod(LoadingSequenceDeltaTime,AnimInterval);
		LoadingSequenceIndex = LoadingSequenceArrayNum > 0 ? (LoadingSequenceIndex + 1) % LoadingSequenceArrayNum : 0;
	}
}

void ULoadingScreenFunctionLibrary::SkipLoadingSequenceFrame()
{
	IncrementLoadingSequenceIndex(2 * GetLoadingSequenceInterval()); 
	LoadingSequenceDeltaTime = 0.0f;
}

UMaterialInterface* ULoadingScreenFunctionLibrary::GetAnimatedMaterial()
{
	return Cast<UMaterialInterface>(GetDefault<ULoadingScreenSettings>()->AnimatedMaterial.TryLoad());
}

FImageSettings ULoadingScreenFunctionLibrary::GetBackgroundImage()
{
	if(BackgroundImageArrayNum != 0 && BackgroundImageIndex >= 0)
	{
		return GetDefault<ULoadingScreenSettings>()->BackgroundImages[BackgroundImageIndex % BackgroundImageArrayNum];
	}
	FImageSettings NullOutput;
	NullOutput.Image = nullptr;
	return NullOutput;
}

UMaterialInterface* ULoadingScreenFunctionLibrary::GetOverlayMaterial()
{
	if(UMaterialInterface* Output = Cast<UMaterialInterface>(GetDefault<ULoadingScreenSettings>()->OverlayMaterial.TryLoad()))
	{
		return Output;
	}
	const FSoftObjectPath TransparentAssetPath("Material'/EasyLoadingScreen/ExampleMaterials/M_FullyTransparent.M_FullyTransparent'");
	return Cast<UMaterialInterface>(TransparentAssetPath.TryLoad());
}

UMaterialInterface* ULoadingScreenFunctionLibrary::GetTransitionMaterial()
{
	return Cast<UMaterialInterface>(GetDefault<ULoadingScreenSettings>()->TransitionMaterial.TryLoad());
}
