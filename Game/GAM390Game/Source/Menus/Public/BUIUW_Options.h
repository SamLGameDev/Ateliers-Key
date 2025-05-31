// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GI_Accessibility.h"
#include "UBaseGameUserSettings.h"
#include "AUW_BaseMenuWidget.h"
#include "LevelSequence.h"
#include "SettingsSave.h"
#include "Components/ComboBox.h"
#include "Components/ComboBoxString.h"
#include "Components/HorizontalBox.h"
#include "Components/RichTextBlock.h"
#include "Components/Slider.h"
#include "BUIUW_Options.generated.h"

class UButton;
class UTextBlock;
class UImage;
class UCanvasPanel;
class UCheckBox;
struct FButtonStyle;

/**
 * 
 */
UCLASS()
class MENUS_API UBUIUW_Options : public UAUW_BaseMenuWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* m_BackgroundImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USlider* BrightnessSlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* BrightnessText;

#pragma region Audio
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USlider* MusicVolumeSlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USlider* SFXVolumeSlider;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USlider* MasterVolumeSlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USlider* DialogueVolumeSlider;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CameraSensitivityValue;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DialogueVolumeValue;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MasterVolumeValue;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MusicVolumeValue;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SFXVolumeValue;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* FOVValue;
	
#pragma endregion

#pragma region Accessability
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UHorizontalBox* hor_SubtitlesSize;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USlider* CameraSensitivitySlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USlider* HeadBobbingSlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HeadBobbingValue;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USlider* FOVSlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UComboBoxString* SubtitleSize_Dropdown;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	URichTextBlock* ExampleSubtitles;

	UPROPERTY(EditAnywhere)
	UDataTable* SmallSubtitleDataTable;

	UPROPERTY(EditAnywhere)
	UDataTable* MedSubtitleDataTable;

	UPROPERTY(EditAnywhere)
	UDataTable* LargeSubtitleDataTable;

	UFUNCTION(BlueprintCallable)
	void UpdateText(UTextBlock* InputText, USlider* InputSlider);

#pragma endregion

	UFUNCTION(BlueprintImplementableEvent)
	void SetPlayerFOV(float FOV);
	
	UFUNCTION(BlueprintCallable)
	void SaveVariables();

	void ApplyBrightnessSettings(const float value);
	
private:
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* m_GraphicsCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* m_WarningCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* m_SoundCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* m_ControlsCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* m_GameplayCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* m_AccessibilityCanvas;

	struct SettingsQuality {
		const FString DisplayName;
		const float Quality;

		SettingsQuality(const FString Name, const float InQuality) : DisplayName(Name), Quality(InQuality) {};
	};

	const TArray<SettingsQuality>  m_QualitySettings = { SettingsQuality("Low", 0), SettingsQuality("Medium", 1), SettingsQuality("High", 2)  ,SettingsQuality("Far", 3), SettingsQuality("SuperFar", 4) };

#pragma region Resolution

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_ResolutionHigher;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_ResolutionLower;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_ResolutionTextFirst;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_ResolutionTextLast;

	int m_CurrentResolutionIndex = 0;

	const TArray<FIntPoint> m_Resolutions = {FIntPoint(720, 480), FIntPoint(1280, 720), FIntPoint(1920, 1080), FIntPoint(2560, 1440) };

	UFUNCTION()
	void OnResolutionHigherClicked();

	UFUNCTION()
	void OnResolutionLowerClicked();

	void SetNewResolution();

	void SetResolutionText(const FIntPoint& resolution);

#pragma endregion

#pragma region WindowMode

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_WindowModeHigher;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_WindowModeLower;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_WindowModeText;

	UFUNCTION()
	void OnWindowModeHigherClicked();

	UFUNCTION()
	void OnWindowModeLowerClicked();

	void SetNewWindowMode();

	void SetWindowModeText();

	int m_WindowModeIndex = 0;

#pragma endregion

#pragma region FrameRate

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_FrameRateHigher;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_FrameRateLower;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_FrameRateText;

	int m_CurrentFrameRateIndex = 0;

	const TArray<int> m_FrameRates = { 30, 60, 120, 240 };

	UFUNCTION()
	void OnFrameRateHigherClicked();

	UFUNCTION()
	void OnFrameRateLowerClicked();

	void SetNewFrameRate();

#pragma endregion

#pragma region ViewDistance

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_ViewDistanceHigher;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_ViewDistanceLower;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_ViewDistanceText;

	int m_CurrentViewDistanceIndex = 0;	

	UFUNCTION()
	void OnViewDistanceHigherClicked();

	UFUNCTION()
	void OnViewDistanceLowerClicked();

	void SetNewViewDistance();

#pragma endregion

#pragma region PostProcessing

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_PostProcessingHigher;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_PostProcessingLower;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_PostProcessingText;

	int m_CurrentPostProcessingIndex = 0;

	UFUNCTION()
	void OnPostProcessingHigherClicked();

	UFUNCTION()
	void OnPostProcessingLowerClicked();

	void SetNewPostProcessing();

#pragma endregion

#pragma region Anti-Aliasing

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_AntiAliasingHigher;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_AntiAliasingLower;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_AntiAliasingText;

	int m_CurrentAntiAliasingIndex = 0;

	UFUNCTION()
	void OnAntiAliasingHigherClicked();

	UFUNCTION()
	void OnAntiAliasingLowerClicked();

	void SetNewAntiAliasing();

#pragma endregion

#pragma region TextureQuality

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_TextureQualityHigher;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_TextureQualityLower;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_TextureQualityText;

	int m_CurrentTextureQualityIndex = 0;

	UFUNCTION()
	void OnTextureQualityHigherClicked();

	UFUNCTION()
	void OnTextureQualityLowerClicked();

	void SetNewTextureQuality();

#pragma endregion

#pragma region ShadowQuality

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_ShadowQualityHigher;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_ShadowQualityLower;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_ShadowQualityText;

	int m_CurrentShadowQualityIndex = 0;

	UFUNCTION()
	void OnShadowQualityHigherClicked();

	UFUNCTION()
	void OnShadowQualityLowerClicked();

	void SetNewShadowQuality();

#pragma endregion

#pragma region VSync

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCheckBox* m_VSyncEnabled;

	UFUNCTION()
	void OnVSyncEnabled(const bool bIsChecked);

#pragma endregion

#pragma region Subtitles

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCheckBox* m_SubtitlesEnabled;

	UFUNCTION()
	void OnSubtitlesCheck(const bool bIsChecked);
	
#pragma endregion

#pragma region Optimal

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_Optimal;


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_OptimalText;

	UFUNCTION()
	void UseOptimalSettings();

#pragma endregion



	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_CancelApply;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_ConfirmApply;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* m_WarningImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_WarningText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_ApplySettings;
	
	UUBaseGameUserSettings* m_Settings;

#pragma region Menus

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_GraphicsMenu;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_SoundMenu;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_ControlsMenu;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_GameplayMenu;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_AccessibilityMenu;

	UCanvasPanel* m_CurrentCanvas;

	void ChangeCanvas(UCanvasPanel* NewCanvas);

	UFUNCTION()
	void ShowGraphics();

	UFUNCTION()
	void ShowSound();

	UFUNCTION()
	void ShowControls();

	UFUNCTION()
	void ShowGameplay();

	UFUNCTION()
	void ShowAccessibility();

	void SetVisibilityOfWarningAndMenus(const ESlateVisibility Warning, const ESlateVisibility Menus);

	void SetMenuVisibility(const ESlateVisibility Visibility);

	UFUNCTION() 
	void ShowWarning();

	UFUNCTION()
	void HideWarning();

#pragma endregion
	
	UFUNCTION()
	void SaveSettings();

	UFUNCTION()
	void LoadVariableSettingsFunc(USettingsSave* SaveGame);

	UFUNCTION()
	void LoadTextSettingsFunc(USettingsSave* SaveGame);
	
	UFUNCTION()
	void SetDropdownFunc(int Selection);

	UFUNCTION()
	void UpdateExampleSubtitlesFunc(int SubtitlesInt);

#pragma region SliderFunctions

	UFUNCTION()
	void HeadBobbingValueChange(float value);

	UFUNCTION()
	void CameraSensValueChange(float value);

	UFUNCTION()
	void CameraSensCapEnd();

	UFUNCTION()
	void FOVSliderValueChange(float value);

	UFUNCTION()
	void FOVSliderCapEnd();

	UFUNCTION()
	void BrightnessSliderValueChange(float value);

	UFUNCTION()
	void BrightnessSliderCapEnd();
	
#pragma endregion

	
#if !WITH_EDITOR
	void Restart();
#endif

	UFUNCTION()
	void InitializeMenus();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_Back;


	UPROPERTY(EditAnywhere)
	FButtonStyle m_UnselctedButton;


	UPROPERTY(EditAnywhere)
	FButtonStyle m_SelctedButton;



	void NativeConstruct() override;

	void UpdateSettingsDisplayedText();

	void SyncSubtitles();

	void SyncVSync();

	void SyncShadowQuality();

	void SyncTextureQuality();

	void SyncAntiAliasing();

	void SyncPostProcessing();

	void SyncViewDistance();

	void SyncFrameRateLock();

	void SyncWindowMode();

	void SyncResolutionSetting();

	UFUNCTION()
	void LoadPreviousMenu();

	void SetUpButtonBindings();

	void SetUpNavigatonButtons();

	void SetUpGraphicOptionButtons();

	void SetUpMenuButtons();

	void SetUpSliders();

	//void SetupCanvases();
};
