// Fill out your copyright notice in the Description page of Project Settings.


#include "GI_Accessibility.h"

#include "UBaseGameUserSettings.h"
#include "SoundManager.h"

void UGI_SanctumSettings::Init()
{
	SyncSubtitlesSettings();
	USoundManager::SetSoundTable(SoundTable);
}

void UGI_SanctumSettings::SyncSubtitlesSettings()
{
	UUBaseGameUserSettings* gameUserSettings = Cast<UUBaseGameUserSettings>(UGameUserSettings::GetGameUserSettings());

	if (gameUserSettings)
	{
		bSubtitlesEnabled = gameUserSettings->bSubtitlesEnabled;
		m_Brightness = gameUserSettings->m_Brightness;
	}
}

