
// Fill out your copyright notice in the Description page of Project Settings.
#include "GI_Accessibility.h"

#include "UBaseGameUserSettings.h"
#include "SettingsSave.h"
#include "Kismet/GameplayStatics.h"

void UGI_SanctumSettings::SetSaveSlot(const FString& SlotName)
{
}

void UGI_SanctumSettings::Init()
{
	Super::Init();
	SyncSubtitlesSettings();
}

void UGI_SanctumSettings::SyncSubtitlesSettings()
{
	UUBaseGameUserSettings* gameUserSettings = Cast<UUBaseGameUserSettings>(UGameUserSettings::GetGameUserSettings());

	if (gameUserSettings)
	{
		bSubtitlesEnabled = gameUserSettings->bSubtitlesEnabled;
		m_Brightness = gameUserSettings->m_Brightness;
		CameraSensitivity = gameUserSettings->CameraSensitivity;
		CameraFov = gameUserSettings->CameraFov;

		if (CameraFov == 0)
		{
			CameraFov = 1;
		}

	}
	if (!UGameplayStatics::DoesSaveGameExist("settings", 0))
	{
		USettingsSave* SaveGame = Cast<USettingsSave>(UGameplayStatics::CreateSaveGameObject(USettingsSave::StaticClass()));
		UGameplayStatics::AsyncSaveGameToSlot(SaveGame, "settings", 0);
	}
}

