// Copyright (c) 2022 Jakub Ferliński.

#include "EasyLoadingScreen.h"

#include "LoadingScreenLayout.h"
#include "MoviePlayer.h"

#define LOCTEXT_NAMESPACE "FEasyLoadingScreenModule"

void FEasyLoadingScreenModule::StartupModule()
{
	if (IsRunningDedicatedServer() || !FSlateApplication::IsInitialized())
	{
		return;
	}

	if (IsMoviePlayerEnabled())
	{
		GetMoviePlayer()->OnPrepareLoadingScreen().AddRaw(this, &FEasyLoadingScreenModule::SetupLoadingScreen);
	}
}

void FEasyLoadingScreenModule::ShutdownModule()
{
	if (!IsRunningDedicatedServer())
	{
		GetMoviePlayer()->OnPrepareLoadingScreen().RemoveAll(this);
	}
}

void FEasyLoadingScreenModule::SetupLoadingScreen() const
{
	FLoadingScreenAttributes LoadingScreen;
	
	LoadingScreen.WidgetLoadingScreen = SNew(SLoadingScreenLayout);
	
	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEasyLoadingScreenModule, EasyLoadingScreen)