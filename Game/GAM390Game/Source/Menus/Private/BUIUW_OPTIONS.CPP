#include "AudioDevice.h"
#include "BUIUW_Options.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameUserSettings.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "BP_SceneManager.h"
#include "GI_Accessibility.h"
#include "Components/CheckBox.h"
#include "Kismet/GameplayStatics.h"
#include "BP_UserWidgetFunctions.h"
#include "SettingsSave.h"
#include "BP_GeneralFunctions.h"
#include "Styling/SlateTypes.h"
#include "SubtitleWidget.h"

void UBUIUW_Options::OnResolutionHigherClicked()
{
	m_CurrentResolutionIndex++;

	if (m_CurrentResolutionIndex == m_Resolutions.Num())
	{
		m_CurrentResolutionIndex--;

		return;

	}

	SetNewResolution();
}

void UBUIUW_Options::OnResolutionLowerClicked()
{
	m_CurrentResolutionIndex--;

	if (m_CurrentResolutionIndex < 0)
	{
		m_CurrentResolutionIndex++;

		return;

	}

	SetNewResolution();
}

void UBUIUW_Options::SetNewResolution()
{

	const FIntPoint resolution = m_Resolutions[m_CurrentResolutionIndex];

	m_Settings->SetScreenResolution(resolution);

	SetResolutionText(resolution);

}

void UBUIUW_Options::SetResolutionText(const FIntPoint& resolution)
{
	const FString resolutionDisplayText = FString::Printf(TEXT("%d"), resolution.X);

	m_ResolutionTextFirst->SetText(FText::FromString(resolutionDisplayText));

	const FString resolutionDisplayTextSecond = FString::Printf(TEXT("%d"), resolution.Y);

	m_ResolutionTextLast->SetText(FText::FromString(resolutionDisplayTextSecond));


}

void UBUIUW_Options::OnWindowModeHigherClicked()
{
	m_WindowModeIndex++;

	//reset the widnow mode if its out of bounds
	if (m_WindowModeIndex == EWindowMode::NumWindowModes)
	{
		m_WindowModeIndex--;

		return;
	}

	SetNewWindowMode();
}

void UBUIUW_Options::OnWindowModeLowerClicked()
{
	m_WindowModeIndex--;

	//reset the widnow mode if its out of bounds
	if (m_WindowModeIndex < 0)
	{
		m_WindowModeIndex++;

		return;
	}

	SetNewWindowMode();

}

void UBUIUW_Options::SetNewWindowMode()
{

	const EWindowMode::Type currentMode = EWindowMode::ConvertIntToWindowMode(m_WindowModeIndex);

	m_Settings->SetFullscreenMode(currentMode);

	SetWindowModeText();


}

void UBUIUW_Options::SetWindowModeText()
{
	const UEnum* windowMode = StaticEnum<EWindowMode::Type>();

	const FString windowModeName = windowMode->GetNameStringByValue(m_WindowModeIndex);

	m_WindowModeText->SetText(FText::FromString(windowModeName));
}

void UBUIUW_Options::OnFrameRateHigherClicked()
{
	m_CurrentFrameRateIndex++;

	if (m_CurrentFrameRateIndex == m_FrameRates.Num())
	{
		m_CurrentFrameRateIndex--;

		return;
	}

	SetNewFrameRate();
}

void UBUIUW_Options::OnFrameRateLowerClicked()
{
	m_CurrentFrameRateIndex--;

	if (m_CurrentFrameRateIndex < 0)
	{
		m_CurrentFrameRateIndex++;

		return;
	}

	SetNewFrameRate();
}

void UBUIUW_Options::SetNewFrameRate()
{

	const int frameRateLock = m_FrameRates[m_CurrentFrameRateIndex];

	m_Settings->SetFrameRateLimit(frameRateLock);

	//there is no FText from int so we have to convert it to a string first
	const FString displayFrameRate = FString::FromInt(frameRateLock);

	m_FrameRateText->SetText(FText::FromString(displayFrameRate));
}

void UBUIUW_Options::OnViewDistanceHigherClicked()
{
	m_CurrentViewDistanceIndex++;

	if (m_CurrentViewDistanceIndex == m_QualitySettings.Num())
	{
		m_CurrentViewDistanceIndex--;

		return;
	}

	SetNewViewDistance();
}

void UBUIUW_Options::OnViewDistanceLowerClicked()
{
	m_CurrentViewDistanceIndex--;

	if (m_CurrentViewDistanceIndex < 0) 
	{
		m_CurrentViewDistanceIndex++;

		return;
	}

	SetNewViewDistance();
}

void UBUIUW_Options::SetNewViewDistance()
{
	const SettingsQuality quality = m_QualitySettings[m_CurrentViewDistanceIndex];

	m_Settings->SetViewDistanceQuality(quality.Quality);

	m_ViewDistanceText->SetText(FText::FromString(quality.DisplayName));

}

void UBUIUW_Options::OnPostProcessingHigherClicked()
{
	m_CurrentPostProcessingIndex++;

	if (m_CurrentPostProcessingIndex == m_QualitySettings.Num()) 
	{
		m_CurrentPostProcessingIndex--;

		return;
	}

	SetNewPostProcessing();
}

void UBUIUW_Options::OnPostProcessingLowerClicked()
{
	m_CurrentPostProcessingIndex--;

	if (m_CurrentPostProcessingIndex < 0)
	{
		m_CurrentPostProcessingIndex++;

		return;
	}

	SetNewPostProcessing();
}

void UBUIUW_Options::SetNewPostProcessing()
{
	const SettingsQuality quality = m_QualitySettings[m_CurrentPostProcessingIndex];

	m_Settings->SetPostProcessingQuality(quality.Quality);

	m_PostProcessingText->SetText(FText::FromString(quality.DisplayName));
}

void UBUIUW_Options::OnAntiAliasingHigherClicked()
{
	m_CurrentAntiAliasingIndex++;

	if (m_CurrentAntiAliasingIndex == m_QualitySettings.Num())
	{
		m_CurrentAntiAliasingIndex--;

		return;
	}

	SetNewAntiAliasing();
}

void UBUIUW_Options::OnAntiAliasingLowerClicked()
{
	m_CurrentAntiAliasingIndex--;

	if (m_CurrentAntiAliasingIndex < 0)
	{
		m_CurrentAntiAliasingIndex++;

		return;
	}

	SetNewAntiAliasing();
}

void UBUIUW_Options::SetNewAntiAliasing()
{
	const SettingsQuality quality = m_QualitySettings[m_CurrentAntiAliasingIndex];

	m_Settings->SetAntiAliasingQuality(quality.Quality);

	m_AntiAliasingText->SetText(FText::FromString(quality.DisplayName));
}

void UBUIUW_Options::OnTextureQualityHigherClicked()
{
	m_CurrentTextureQualityIndex++;

	if (m_CurrentTextureQualityIndex == m_QualitySettings.Num()) 
	{
		m_CurrentTextureQualityIndex--;

		return;
	}

	SetNewTextureQuality();
}

void UBUIUW_Options::OnTextureQualityLowerClicked()
{
	m_CurrentTextureQualityIndex--;

	if (m_CurrentTextureQualityIndex < 0)
	{
		m_CurrentTextureQualityIndex++;

		return;
	}

	SetNewTextureQuality();
}

void UBUIUW_Options::SetNewTextureQuality()
{
	const SettingsQuality quality = m_QualitySettings[m_CurrentTextureQualityIndex];

	m_Settings->SetTextureQuality(quality.Quality);

	m_TextureQualityText->SetText(FText::FromString(quality.DisplayName));
}

void UBUIUW_Options::OnShadowQualityHigherClicked()
{
	m_CurrentShadowQualityIndex++;

	if (m_CurrentShadowQualityIndex == m_QualitySettings.Num())
	{
		m_CurrentShadowQualityIndex--;

		return;
	}

	SetNewShadowQuality();
}

void UBUIUW_Options::OnShadowQualityLowerClicked()
{
	m_CurrentShadowQualityIndex--;

	if (m_CurrentShadowQualityIndex < 0)
	{
		m_CurrentShadowQualityIndex++;

		return;
	}

	SetNewShadowQuality();
}

void UBUIUW_Options::SetNewShadowQuality()
{
   	const SettingsQuality quality = m_QualitySettings[m_CurrentShadowQualityIndex];

	m_Settings->SetShadowQuality(quality.Quality);

	m_ShadowQualityText->SetText(FText::FromString(quality.DisplayName));
}

void UBUIUW_Options::OnVSyncEnabled(const bool bIsChecked)
{
	m_VSyncEnabled->SetIsChecked(bIsChecked);

	m_Settings->SetVSyncEnabled(bIsChecked);
}

void UBUIUW_Options::OnSubtitlesCheck(const bool bIsChecked)
{
	m_SubtitlesEnabled->SetIsChecked(bIsChecked);

	hor_SubtitlesSize->SetVisibility(bIsChecked ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	
	m_Settings->SetSubtitlesEnabled(bIsChecked);

	m_Settings->ApplySettings(false);

	
}

void UBUIUW_Options::UseOptimalSettings()
{
	m_Settings->RunHardwareBenchmark();

	m_Settings->ApplyHardwareBenchmarkResults();


	//Frame rate and resoution can be outside of the set ranges when using optimal
	//this will mess up the indexing when switching them again.
	//to fix this, we just dont allow them to go outside the set bounds
	if (!m_FrameRates.Contains(m_Settings->GetFrameRateLimit()))
	{
		m_Settings->SetFrameRateLimit(60);
	}
	
	if (!m_Resolutions.Contains(m_Settings->GetScreenResolution()))
	{
		m_Settings->SetScreenResolution(FIntPoint(2560, 1440));
	}

	UpdateSettingsDisplayedText();
}

void UBUIUW_Options::ChangeCanvas(UCanvasPanel* NewCanvas)
{
	m_CurrentCanvas->SetVisibility(ESlateVisibility::Hidden);

	NewCanvas->SetVisibility(ESlateVisibility::Visible);

	m_CurrentCanvas = NewCanvas;

	m_Optimal->GetParent()->SetVisibility(ESlateVisibility::Hidden);
	m_ApplySettings->GetParent()->SetVisibility(ESlateVisibility::Hidden);
}

void UBUIUW_Options::ShowGraphics()
{
	ChangeCanvas(m_GraphicsCanvas);
	m_GraphicsMenu->SetStyle(m_SelctedButton);
	m_GameplayMenu->SetStyle(m_UnselctedButton);
	m_SoundMenu->SetStyle(m_UnselctedButton);
	m_AccessibilityMenu->SetStyle(m_UnselctedButton);
	m_ControlsMenu->SetStyle(m_UnselctedButton);
	m_Optimal->GetParent()->SetVisibility(ESlateVisibility::Visible);
	m_ApplySettings->GetParent()->SetVisibility(ESlateVisibility::Visible);

}

void UBUIUW_Options::ShowSound()
{
	ChangeCanvas(m_SoundCanvas);
	m_GraphicsMenu->SetStyle(m_UnselctedButton);
	m_GameplayMenu->SetStyle(m_UnselctedButton);
	m_SoundMenu->SetStyle(m_SelctedButton);
	m_AccessibilityMenu->SetStyle(m_UnselctedButton);
	m_ControlsMenu->SetStyle(m_UnselctedButton);
}

void UBUIUW_Options::ShowControls()
{
	ChangeCanvas(m_ControlsCanvas);
	m_GraphicsMenu->SetStyle(m_UnselctedButton);
	m_GameplayMenu->SetStyle(m_UnselctedButton);
	m_SoundMenu->SetStyle(m_UnselctedButton);
	m_AccessibilityMenu->SetStyle(m_UnselctedButton);
	m_ControlsMenu->SetStyle(m_SelctedButton);
}

void UBUIUW_Options::ShowGameplay()
{
	ChangeCanvas(m_GameplayCanvas);
	m_GraphicsMenu->SetStyle(m_UnselctedButton);
	m_GameplayMenu->SetStyle(m_SelctedButton);
	m_SoundMenu->SetStyle(m_UnselctedButton);
	m_AccessibilityMenu->SetStyle(m_UnselctedButton);
	m_ControlsMenu->SetStyle(m_UnselctedButton);
}

void UBUIUW_Options::ShowAccessibility()
{
	ChangeCanvas(m_AccessibilityCanvas);
	m_GraphicsMenu->SetStyle(m_UnselctedButton);
	m_GameplayMenu->SetStyle(m_UnselctedButton);
	m_SoundMenu->SetStyle(m_UnselctedButton);
	m_AccessibilityMenu->SetStyle(m_SelctedButton);
	m_ControlsMenu->SetStyle(m_UnselctedButton);
}

void UBUIUW_Options::SetVisibilityOfWarningAndMenus(const ESlateVisibility Warning, const ESlateVisibility Menus)
{
	SetMenuVisibility(Menus);

	m_WarningCanvas->SetVisibility(Warning);
}

void UBUIUW_Options::SetMenuVisibility(const ESlateVisibility NewVisibility)
{
	m_CurrentCanvas->SetVisibility(NewVisibility);

	m_GraphicsCanvas->SetVisibility(NewVisibility);

	m_GameplayCanvas->SetVisibility(NewVisibility);

	m_SoundCanvas->SetVisibility(NewVisibility);

	m_ControlsCanvas->SetVisibility(NewVisibility);

	m_AccessibilityCanvas->SetVisibility(NewVisibility);

	

}

void UBUIUW_Options::ShowWarning()
{
	SetVisibilityOfWarningAndMenus(ESlateVisibility::Visible, ESlateVisibility::Hidden);

	m_GraphicsMenu->GetParent()->SetVisibility(ESlateVisibility::Hidden);
	m_GameplayMenu->GetParent()->SetVisibility(ESlateVisibility::Hidden);
	m_SoundMenu->GetParent()->SetVisibility(ESlateVisibility::Hidden);
	m_AccessibilityMenu->GetParent()->SetVisibility(ESlateVisibility::Hidden);
	m_ControlsMenu->GetParent()->SetVisibility(ESlateVisibility::Hidden);

	m_Back->GetParent()->SetVisibility(ESlateVisibility::Hidden);
	m_Optimal->GetParent()->SetVisibility(ESlateVisibility::Hidden);
	m_ApplySettings->GetParent()->SetVisibility(ESlateVisibility::Hidden);
	m_BackgroundImage->GetParent()->SetVisibility(ESlateVisibility::Hidden);
}

void UBUIUW_Options::HideWarning()
{
	SetVisibilityOfWarningAndMenus(ESlateVisibility::Hidden, ESlateVisibility::Hidden);
	m_CurrentCanvas->SetVisibility(ESlateVisibility::Visible);
	m_GraphicsMenu->GetParent()->SetVisibility(ESlateVisibility::Visible);
	m_GameplayMenu->GetParent()->SetVisibility(ESlateVisibility::Visible);
	m_SoundMenu->GetParent()->SetVisibility(ESlateVisibility::Visible);
	m_AccessibilityMenu->GetParent()->SetVisibility(ESlateVisibility::Visible);
	m_ControlsMenu->GetParent()->SetVisibility(ESlateVisibility::Visible);

	m_Back->GetParent()->SetVisibility(ESlateVisibility::Visible);
	m_Optimal->GetParent()->SetVisibility(ESlateVisibility::Visible);
	m_ApplySettings->GetParent()->SetVisibility(ESlateVisibility::Visible);
	m_BackgroundImage->GetParent()->SetVisibility(ESlateVisibility::Visible);
}

void UBUIUW_Options::SaveSettings()
{
	m_Settings->ApplySettings(false);

	m_Settings->SaveSettings();

	UBP_SceneManager::Quit(this);

	//only restart if not in editor, as otherwise it will close down the editor

#if !WITH_EDITOR
	Restart();
#endif
}

#if !WITH_EDITOR
void UBUIUW_Options::Restart()
{


	const FString currentExe = FPlatformProcess::ExecutablePath();

	const FString commandLine = FCommandLine::Get();

	FPlatformProcess::CreateProc(*currentExe, *commandLine, true, false, false, nullptr, 0, nullptr, nullptr);


}
#endif

void UBUIUW_Options::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetUpButtonBindings();
	SetUpSliders();


	m_Settings = Cast<UUBaseGameUserSettings>(UGameUserSettings::GetGameUserSettings());

	if (!m_Settings)
	{

		UE_LOG(LogTemp, Error, TEXT("GameUserSettings instance is null in UBUIUW_Options::NativeConstruct"));
		return;
	}
	m_Settings->LoadSettings();

	m_Settings->WorldContext = this;
	m_Settings->ApplySettings(false);

	if(UGameplayStatics::DoesSaveGameExist("settings", 0))
	{
		USettingsSave* SaveGame = Cast<USettingsSave>(UGameplayStatics::LoadGameFromSlot("settings", 0));

		if(!SaveGame)
		{
			return;
		}

		LoadVariableSettingsFunc(SaveGame);
		LoadTextSettingsFunc(SaveGame);
	}
	else
	{
		USettingsSave* SaveGame = Cast<USettingsSave>(UGameplayStatics::CreateSaveGameObject(USettingsSave::StaticClass()));
		UGameplayStatics::AsyncSaveGameToSlot(SaveGame, "settings", 0);
		m_Settings->SetFrameRateLimit(60);
		LoadVariableSettingsFunc(SaveGame);
		LoadTextSettingsFunc(SaveGame);
	}

	InitializeMenus();

	UpdateSettingsDisplayedText();


}

void UBUIUW_Options::LoadVariableSettingsFunc(USettingsSave* SaveGame)
{
	MusicVolumeSlider->SetValue(SaveGame->MusicVolume);
	SFXVolumeSlider->SetValue(SaveGame->SFXVolume);
	MasterVolumeSlider->SetValue(SaveGame->MasterVolume);
	DialogueVolumeSlider->SetValue(SaveGame->DialogueVolume);
	CameraSensitivitySlider->SetValue(SaveGame->CameraSensitivity);
	HeadBobbingSlider->SetValue(SaveGame->HeadBobbing);
	FOVSlider->SetValue(SaveGame->FOVValue);
	SetDropdownFunc(SaveGame->SubtitleSize);
}

void UBUIUW_Options::LoadTextSettingsFunc(USettingsSave* SaveGame)
{
	CameraSensitivityValue->SetText(FText::AsNumber(FMath::RoundToInt(SaveGame->CameraSensitivity * 100.0f)));
	DialogueVolumeValue->SetText(FText::AsNumber(FMath::RoundToInt(SaveGame->DialogueVolume * 100.0f)));
	MasterVolumeValue->SetText(FText::AsNumber(FMath::RoundToInt(SaveGame->MasterVolume * 100.0f)));
	MusicVolumeValue->SetText(FText::AsNumber(FMath::RoundToInt(SaveGame->MusicVolume * 100.0f)));
	SFXVolumeValue->SetText(FText::AsNumber(FMath::RoundToInt(SaveGame->SFXVolume * 100.0f)));
	HeadBobbingValue->SetText(FText::AsNumber(FMath::RoundToInt(SaveGame->HeadBobbing * 10.0f)));
	FOVValue->SetText(FText::AsNumber(FMath::RoundToInt(SaveGame->FOVValue * 100.0f)));
	UpdateExampleSubtitlesFunc(SaveGame->SubtitleSize);
}

void UBUIUW_Options::SetDropdownFunc(int Selection)
{
	SubtitleSize_Dropdown->SetSelectedIndex(Selection);
}

void UBUIUW_Options::UpdateExampleSubtitlesFunc(int SubtitlesInt)
{
	switch(SubtitlesInt)
	{
	case 1:
		ExampleSubtitles->SetTextStyleSet(SmallSubtitleDataTable);
		break;
	case 2:
		ExampleSubtitles->SetTextStyleSet(MedSubtitleDataTable);
		break;
	case 3:
		ExampleSubtitles->SetTextStyleSet(LargeSubtitleDataTable);
		break;
	}
}

void UBUIUW_Options::SaveVariables()
{
	USettingsSave* Save = Cast<USettingsSave>(UGameplayStatics::LoadGameFromSlot("settings", 0));

	if(!Save)
	{
		Save = Cast<USettingsSave>(UGameplayStatics::CreateSaveGameObject(USettingsSave::StaticClass()));
	}

	Save->SFXVolume = SFXVolumeSlider->GetValue();
	Save->MusicVolume = MusicVolumeSlider->GetValue();
	Save->MasterVolume = MasterVolumeSlider->GetValue();
	Save->DialogueVolume = DialogueVolumeSlider->GetValue();
	Save->SubtitleSize = Cast<UGI_SanctumSettings>(GetGameInstance())->m_SubtitleSize;
	Save->CameraSensitivity = CameraSensitivitySlider->GetValue();
	Save->HeadBobbing = HeadBobbingSlider->GetValue();
	Save->FOVValue = FOVSlider->GetValue();
	m_Settings->ApplySettings(false);
	SetPlayerFOV(Save->FOVValue);

	UGameplayStatics::SaveGameToSlot(Save, "settings", 0);
}

void UBUIUW_Options::ApplyBrightnessSettings(const float value)
{
	for (IInterface_PostProcessVolume* IPPVolume : GetWorld()->PostProcessVolumes)
	{
		FPostProcessVolumeProperties props = IPPVolume->GetProperties();
		if (props.bIsUnbound)
		{
			FPostProcessSettings* settings = (FPostProcessSettings*)props.Settings;
			settings->AutoExposureMinBrightness = value * -1;
			settings->AutoExposureMaxBrightness = value * -1;
		}
	}
}


void UBUIUW_Options::HeadBobbingValueChange(float value)
{
	HeadBobbingValue->SetText(FText::AsNumber(FMath::RoundToInt(HeadBobbingSlider->GetValue() * 10)));
}

void UBUIUW_Options::CameraSensValueChange(float value)
{
	UpdateText(CameraSensitivityValue, CameraSensitivitySlider);
}

void UBUIUW_Options::CameraSensCapEnd()
{
	SaveVariables();
	UpdateText(CameraSensitivityValue, CameraSensitivitySlider);
}

void UBUIUW_Options::FOVSliderValueChange(float value)
{
	UpdateText(FOVValue, FOVSlider);
}

void UBUIUW_Options::FOVSliderCapEnd()
{
	SaveVariables();
	UpdateText(FOVValue, FOVSlider);
}

void UBUIUW_Options::BrightnessSliderValueChange(float value)
{
	ApplyBrightnessSettings(value);
	UpdateText(BrightnessText, BrightnessSlider);
}

void UBUIUW_Options::BrightnessSliderCapEnd()
{
	m_Settings->m_Brightness = BrightnessSlider->GetValue();
	SaveVariables();
	UpdateText(BrightnessText, BrightnessSlider);
}


void UBUIUW_Options::InitializeMenus()
{
	//we start on the graphics menu, and we then make everything hidden, then enable the current menu.
	//its a bit less efficent than disabling everything except the current canvas, but its clean
	m_CurrentCanvas = m_GraphicsCanvas;

	SetVisibilityOfWarningAndMenus(ESlateVisibility::Hidden, ESlateVisibility::Hidden);

	m_CurrentCanvas->SetVisibility(ESlateVisibility::Visible);

	ShowGraphics();
}


void UBUIUW_Options::UpdateSettingsDisplayedText()
{
	SyncResolutionSetting();

	SyncWindowMode();

	SyncFrameRateLock();

	SyncViewDistance();

	SyncPostProcessing();

	SyncAntiAliasing();

	SyncTextureQuality();

	SyncShadowQuality();


	SyncVSync();

	SyncSubtitles();

	UGI_SanctumSettings* gameInstance = Cast<UGI_SanctumSettings>(GetWorld()->GetGameInstance());

	BrightnessSlider->SetValue(gameInstance->m_Brightness);

	UpdateText(BrightnessText, BrightnessSlider);
}

void UBUIUW_Options::SyncSubtitles()
{
	const bool bSubtitles = m_Settings->bSubtitlesEnabled;

	m_SubtitlesEnabled->SetIsChecked(bSubtitles);
}

void UBUIUW_Options::SyncVSync()
{
	const bool bVSync = m_Settings->IsVSyncEnabled();

	m_VSyncEnabled->SetIsChecked(bVSync);
}

void UBUIUW_Options::SyncShadowQuality()
{
	m_CurrentShadowQualityIndex = m_Settings->GetShadowQuality();

	m_ShadowQualityText->SetText(FText::FromString(m_QualitySettings[m_CurrentShadowQualityIndex].DisplayName));
}

void UBUIUW_Options::SyncTextureQuality()
{
	m_CurrentTextureQualityIndex = m_Settings->GetTextureQuality();

	m_TextureQualityText->SetText(FText::FromString(m_QualitySettings[m_CurrentTextureQualityIndex].DisplayName));
}

void UBUIUW_Options::SyncAntiAliasing()
{
	m_CurrentAntiAliasingIndex = m_Settings->GetAntiAliasingQuality();

	m_AntiAliasingText->SetText(FText::FromString(m_QualitySettings[m_CurrentAntiAliasingIndex].DisplayName));
}

void UBUIUW_Options::SyncPostProcessing()
{
	m_CurrentPostProcessingIndex = m_Settings->GetPostProcessingQuality();

	m_PostProcessingText->SetText(FText::FromString(m_QualitySettings[m_CurrentPostProcessingIndex].DisplayName));
}

void UBUIUW_Options::SyncViewDistance()
{
	m_CurrentViewDistanceIndex = m_Settings->GetViewDistanceQuality();

	m_ViewDistanceText->SetText(FText::FromString(m_QualitySettings[m_CurrentViewDistanceIndex].DisplayName));
}

void UBUIUW_Options::SyncFrameRateLock()
{
	const int frameRateLock = m_Settings->GetFrameRateLimit();

	const FString displayFrameRate = FString::FromInt(frameRateLock);

	//update the index so its at the current limit
	m_FrameRates.Find(frameRateLock, m_CurrentFrameRateIndex);

	m_FrameRateText->SetText(FText::FromString(displayFrameRate));
}

void UBUIUW_Options::SyncWindowMode()
{
	EWindowMode::Type currentMode = m_Settings->GetFullscreenMode();

	m_WindowModeIndex = static_cast<int64>(currentMode);

	SetWindowModeText();
}

void UBUIUW_Options::SyncResolutionSetting()
{
	const FIntPoint resolution = m_Settings->GetScreenResolution();

	//update the index so its at the current limit
	m_Resolutions.Find(resolution, m_CurrentResolutionIndex);

	SetResolutionText(resolution);
}

void UBUIUW_Options::LoadPreviousMenu()
{
	UBP_UserWidgetFunctions::ChangeWidget(this, m_PreviousMenu);
}

void UBUIUW_Options::UpdateText(UTextBlock* InputText, USlider* InputSlider)
{
	InputText->SetText(FText::AsNumber(FMath::RoundToInt(InputSlider->GetValue() * 100.0f)));

}



void UBUIUW_Options::SetUpButtonBindings()
{
	SetUpGraphicOptionButtons();

	SetUpNavigatonButtons();

	SetUpMenuButtons();
}

void UBUIUW_Options::SetUpNavigatonButtons()
{
	m_Optimal->OnClicked.AddDynamic(this, &UBUIUW_Options::UseOptimalSettings);

	m_Back->OnClicked.AddDynamic(this, &UBUIUW_Options::LoadPreviousMenu);

	m_ApplySettings->OnClicked.AddDynamic(this, &UBUIUW_Options::ShowWarning);

	m_ConfirmApply->OnClicked.AddDynamic(this, &UBUIUW_Options::SaveSettings);

	m_CancelApply->OnClicked.AddDynamic(this, &UBUIUW_Options::HideWarning);
}

void UBUIUW_Options::SetUpGraphicOptionButtons()
{
	m_ResolutionHigher->OnClicked.AddDynamic(this, &UBUIUW_Options::OnResolutionHigherClicked);
	m_ResolutionLower->OnClicked.AddDynamic(this, &UBUIUW_Options::OnResolutionLowerClicked);

	m_WindowModeHigher->OnClicked.AddDynamic(this, &UBUIUW_Options::OnWindowModeHigherClicked);
	m_WindowModeLower->OnClicked.AddDynamic(this, &UBUIUW_Options::OnWindowModeLowerClicked);

	m_FrameRateHigher->OnClicked.AddDynamic(this, &UBUIUW_Options::OnFrameRateHigherClicked);
	m_FrameRateLower->OnClicked.AddDynamic(this, &UBUIUW_Options::OnFrameRateLowerClicked);

	m_ViewDistanceHigher->OnClicked.AddDynamic(this, &UBUIUW_Options::OnViewDistanceHigherClicked);
	m_ViewDistanceLower->OnClicked.AddDynamic(this, &UBUIUW_Options::OnViewDistanceLowerClicked);

	m_PostProcessingHigher->OnClicked.AddDynamic(this, &UBUIUW_Options::OnPostProcessingHigherClicked);
	m_PostProcessingLower->OnClicked.AddDynamic(this, &UBUIUW_Options::OnPostProcessingLowerClicked);

	m_AntiAliasingHigher->OnClicked.AddDynamic(this, &UBUIUW_Options::OnAntiAliasingHigherClicked);
	m_AntiAliasingLower->OnClicked.AddDynamic(this, &UBUIUW_Options::OnAntiAliasingLowerClicked);

	m_TextureQualityHigher->OnClicked.AddDynamic(this, &UBUIUW_Options::OnTextureQualityHigherClicked);
	m_TextureQualityLower->OnClicked.AddDynamic(this, &UBUIUW_Options::OnTextureQualityLowerClicked);

	m_ShadowQualityHigher->OnClicked.AddDynamic(this, &UBUIUW_Options::OnShadowQualityHigherClicked);
	m_ShadowQualityLower->OnClicked.AddDynamic(this, &UBUIUW_Options::OnShadowQualityLowerClicked);

	m_VSyncEnabled->OnCheckStateChanged.AddDynamic(this, &UBUIUW_Options::OnVSyncEnabled);

	m_SubtitlesEnabled->OnCheckStateChanged.AddDynamic(this, &UBUIUW_Options::OnSubtitlesCheck);
}

void UBUIUW_Options::SetUpMenuButtons()
{
	m_GraphicsMenu->OnClicked.AddDynamic(this, &UBUIUW_Options::ShowGraphics);

	m_SoundMenu->OnClicked.AddDynamic(this, &UBUIUW_Options::ShowSound);

	m_ControlsMenu->OnClicked.AddDynamic(this, &UBUIUW_Options::ShowControls);

	m_GameplayMenu->OnClicked.AddDynamic(this, &UBUIUW_Options::ShowGameplay);

	m_AccessibilityMenu->OnClicked.AddDynamic(this, &UBUIUW_Options::ShowAccessibility);
}

void UBUIUW_Options::SetUpSliders()
{
	HeadBobbingSlider->OnValueChanged.AddDynamic(this, &UBUIUW_Options::HeadBobbingValueChange);
	HeadBobbingSlider->OnMouseCaptureEnd.AddDynamic(this, &UBUIUW_Options::SaveVariables);
	CameraSensitivitySlider->OnValueChanged.AddDynamic(this, &UBUIUW_Options::CameraSensValueChange);
	CameraSensitivitySlider->OnMouseCaptureEnd.AddDynamic(this, &UBUIUW_Options::CameraSensCapEnd);
	FOVSlider->OnValueChanged.AddDynamic(this, &UBUIUW_Options::FOVSliderValueChange);
	FOVSlider->OnMouseCaptureEnd.AddDynamic(this, &UBUIUW_Options::FOVSliderCapEnd);
	BrightnessSlider->OnValueChanged.AddDynamic(this, &UBUIUW_Options::BrightnessSliderValueChange);
	BrightnessSlider->OnMouseCaptureEnd.AddDynamic(this, &UBUIUW_Options::BrightnessSliderCapEnd);
}