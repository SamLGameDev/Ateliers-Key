// Fill out your copyright notice in the Description page of Project Settings.


#include "UBaseGameUserSettings.h"

#include "GI_Accessibility.h"
#include "Kismet/GameplayStatics.h"

UUBaseGameUserSettings::UUBaseGameUserSettings() : bSubtitlesEnabled(false)
{
}

void UUBaseGameUserSettings::ApplySettings(bool bCheckForCommandLineOverrides)
{
	Super::ApplySettings(bCheckForCommandLineOverrides);


	UGameInstance* instance = UGameplayStatics::GetGameInstance(WorldContext);

	if (!instance)
	{
		return;
	}

	UGI_SanctumSettings* gameInstance = Cast<UGI_SanctumSettings>(instance);
	
	if (gameInstance)
	{
		gameInstance->bSubtitlesEnabled = bSubtitlesEnabled;

		gameInstance->m_Brightness = m_Brightness;

		gameInstance->CameraSensitivity = CameraSensitivity;

	}

	SaveSettings();
}

void UUBaseGameUserSettings::SetSubtitlesEnabled(bool bEnabled)
{
	bSubtitlesEnabled = bEnabled;

	SaveSettings();
}

bool UUBaseGameUserSettings::GetSubtitlesEnabled()
{
	return bSubtitlesEnabled;
}

void UUBaseGameUserSettings::SaveSettings()
{
	GConfig->SetBool
	(
		TEXT("/Script/GAM390Game.UBaseGameUserSettings"),
		TEXT("SubtitlesEnabled"),
		bSubtitlesEnabled,
		GGameIni
	);

	GConfig->SetFloat
	(
		TEXT("/Script/GAM390Game.UBaseGameUserSettings"),
		TEXT("Brightness"),
		m_Brightness,
		GGameIni
	);

	GConfig->SetFloat
	(
	TEXT("/Script/GAM390Game.UBaseGameUserSettings"),
	TEXT("CameraSensitivity"),
	CameraSensitivity,
	GGameIni
	);

	Super::SaveSettings();
}

void UUBaseGameUserSettings::LoadSettings(bool bForceReload)
{
	Super::LoadSettings(bForceReload);

	if (GConfig)
	{
		GConfig->GetBool
		(
			TEXT("/Script/GAM390Game.UBaseGameUserSettings"),
			TEXT("SubtitlesEnabled"),
			bSubtitlesEnabled,
			GGameIni
		);
		GConfig->GetFloat
		(
			TEXT("/Script/GAM390Game.UBaseGameUserSettings"),
			TEXT("Brightness"),
			m_Brightness,
			GGameIni
		);

		GConfig->GetFloat
		(
		TEXT("/Script/GAM390Game.UBaseGameUserSettings"),
		TEXT("CameraSensitivity"),
		CameraSensitivity,
		GGameIni
		);
	}
}


