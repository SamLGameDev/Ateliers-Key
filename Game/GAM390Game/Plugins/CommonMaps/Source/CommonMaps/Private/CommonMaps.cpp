#include "CommonMaps.h"
#include "CommonMapsSettings.h"

#if WITH_EDITOR
#include "ISettingsModule.h"
#endif

void FCommonMapsModule::StartupModule()
{
#if WITH_EDITOR
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
#endif
}

void FCommonMapsModule::ShutdownModule()
{
#if WITH_EDITOR
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "Common Maps");
	}
#endif
}

IMPLEMENT_MODULE(FCommonMapsModule, CommonMaps)