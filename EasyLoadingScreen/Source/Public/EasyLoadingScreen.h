// Copyright (c) 2022 Jakub Ferliński.

#pragma once

class FEasyLoadingScreenModule final : public IModuleInterface
{
	
protected:
	
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool IsGameModule() const override { return true; }

private:
	
	void SetupLoadingScreen() const;
	void SetupMoviePlayer(const bool StartupScreen) const;
};
