// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DiscordLocalPlayerSubsystem.h" 
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

	UFUNCTION()
	void OnDiscordStatusChanged(
		EDiscordClientStatus Status,
		EDiscordClientError Error,
		int32 ErrorDetail
	);

	UFUNCTION(BlueprintCallable, Category="Discord")
	void SetDiscordPresence(FString State, FString Details);

	UFUNCTION(BlueprintCallable, Category="Discord")
	void SetDiscordPresenceDetailsOnly(FString Details);

	UFUNCTION()
	void OnDiscordLogMessage(FString Message, EDiscordLoggingSeverity Severity);

	void OnDiscordAuthorizeCompleted(UDiscordClientResult* Result, FString Code, FString RedirectUri);
	void OnDiscordTokenExchange(UDiscordClientResult* Result, FString AccessToken, FString RefreshToken,
		EDiscordAuthorizationTokenType TokenType, int32 ExpiresIn, FString Scope);
	void OnDiscordTokenUpdated(UDiscordClientResult* Result);

	UFUNCTION(BlueprintCallable, Category="Discord")
	void DiscordConnect();

	UPROPERTY()
	UDiscordAuthorizationCodeVerifier* CodeVerifier;

	UPROPERTY()
	UDiscordLocalPlayerSubsystem* Discord;

	UPROPERTY(BlueprintReadOnly)
	float CameraSensitivity;

	UPROPERTY(BlueprintReadOnly)
	float CameraFov;

	UPROPERTY(BlueprintReadWrite)
	int killedEnemies = 0;

	UPROPERTY(BlueprintReadWrite)
	int pickedUpLoreItems = 0;

	UPROPERTY(BlueprintReadWrite)
	int numOfDeaths = 0;

	virtual void Init() override;

	void SyncSubtitlesSettings();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> QuestTable;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> SoundsTable;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPrimaryDataAsset> PoolingConfig;
};