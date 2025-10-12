// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SettingsSave.generated.h"

/**
 * 
 */
UCLASS()
class USERSETTINGS_API USettingsSave : public USaveGame
{
	GENERATED_BODY()

public:
	USettingsSave();

	UPROPERTY(BlueprintReadWrite)
	float SFXVolume;

	UPROPERTY(BlueprintReadWrite)
	float MusicVolume;

	UPROPERTY(BlueprintReadWrite)
	float MasterVolume;

	UPROPERTY(BlueprintReadWrite)
	float DialogueVolume;

	UPROPERTY(BlueprintReadWrite)
	int SubtitleSize;

	UPROPERTY(BlueprintReadWrite)
	float CameraSensitivity;
	
	UPROPERTY(BlueprintReadWrite)
	float FOVValue;
};
