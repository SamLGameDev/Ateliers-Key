// Fill out your copyright notice in the Description page of Project Settings.

#include "CommonMaps.h"
#include "CommonMapsSettings.h"
#include "ISettingsModule.h"

void FCommonMapsModule::StartupModule()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings(
			"Project",
			"Plugins",
			"Common Maps",
			FText::FromString("Common Maps"),
			FText::FromString("Configure Common Maps asset path settings"),
			GetMutableDefault<UCommonMapsSettings>()
		);
	}
}

void FCommonMapsModule::ShutdownModule()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "Common Maps");
	}
}

IMPLEMENT_MODULE(FCommonMapsModule, CommonMaps)