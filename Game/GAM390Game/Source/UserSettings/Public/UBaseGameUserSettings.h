// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "UBaseGameUserSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game)
class USERSETTINGS_API UUBaseGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config)
	bool bSubtitlesEnabled;

	UPROPERTY(Config)
	float m_Brightness;

	UPROPERTY(Config)
	float CameraSensitivity;

	UObject* WorldContext;

	UUBaseGameUserSettings();

	UFUNCTION()
	void SetSubtitlesEnabled(bool bEnabled);

	UFUNCTION()
	bool GetSubtitlesEnabled();

	virtual void ApplySettings(bool bCheckForCommandLineOverrides) override;

	virtual void SaveSettings() override;

	virtual void LoadSettings(bool bForceReload = false) override;
	
};
