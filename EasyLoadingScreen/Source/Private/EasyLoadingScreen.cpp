// Copyright (c) 2022 Jakub Ferliński.

#include "EasyLoadingScreen.h"

#include "LoadingScreenLayout.h"
#include "LoadingScreenSettings.h"
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

	SetupMoviePlayer(true);
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
	SetupMoviePlayer(false);
}

void FEasyLoadingScreenModule::SetupMoviePlayer(const bool StartupScreen) const
{
	const TArray<FString> MoviesList = StartupScreen ? GetDefault<ULoadingScreenSettings>()->SplashScreenMovies : TArray<FString>{};

	FLoadingScreenAttributes LoadingScreen;
	LoadingScreen.bMoviesAreSkippable = false;
	LoadingScreen.bAllowInEarlyStartup = StartupScreen;
	LoadingScreen.MoviePaths = MoviesList;
	
	if (!StartupScreen)
	{
		LoadingScreen.WidgetLoadingScreen = SNew(SLoadingScreenLayout);
	}
	else
	{
		//LoadingScreen.bWaitForManualStop = true;
		// Ensure startup movie was played
	}
	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEasyLoadingScreenModule, EasyLoadingScreen)