// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GI_Accessibility.generated.h"

static TAutoConsoleVariable<int32> CVarSavingEnabled(
	TEXT("SavingSystem.Enabled"),
	1,
	TEXT("Disable the save system = 0, Enable = 1"),
	ECVF_Default);

/**
 * rename from GI_Accessibility, but references are still that, so you might be looking for that
 */
UCLASS()
class USERSETTINGS_API UGI_SanctumSettings : public UGameInstance
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSubtitlesEnabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int m_SubtitleSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_Brightness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ControllerVibration;

	UPROPERTY(BlueprintReadOnly)
	float CameraSensitivity;

	UFUNCTION(BlueprintCallable)
	void SetSaveSlot(const FString& SlotName);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetSaveSlot();

	UPROPERTY(BlueprintReadOnly)
	float CameraFov;

	UPROPERTY(BlueprintReadWrite)
	int EnemyKills;

	virtual void Init() override;

	void SyncSubtitlesSettings();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> QuestTable;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> SoundsTable;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPrimaryDataAsset> PoolingConfig;

protected:

	UPROPERTY(BlueprintReadOnly)
	FString CurrentSaveSlot = "Save0";

	
};
