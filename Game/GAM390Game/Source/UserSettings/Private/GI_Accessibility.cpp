// Fill out your copyright notice in the Description page of Project Settings.


#include "GI_Accessibility.h"

#include "UBaseGameUserSettings.h"

void UGI_SanctumSettings::Init()
{
	SyncSubtitlesSettings();
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

