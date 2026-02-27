// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AtelierSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class GAM390GAME_API UAtelierSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FVector RestartLocation;

	UPROPERTY(BlueprintReadOnly)
	FRotator RestartRotation;

	UPROPERTY(BlueprintReadOnly)
	TArray<TSoftObjectPtr<UWorld>>  CombatEncounters;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FString>  WorldsToLoad;

	UPROPERTY(BlueprintReadOnly)
	FString BaseMap;

	UPROPERTY(BlueprintReadOnly)
	FString StreamedLevel;

	UPROPERTY(BlueprintReadOnly)
	bool bHasAssultRifle;
	UPROPERTY(BlueprintReadOnly)
	bool bHasSniper;
	UPROPERTY(BlueprintReadOnly)
	bool bHasShotgun;
	
	UPROPERTY(BlueprintReadOnly)
	uint8 QuestStage;
	
	UPROPERTY(BlueprintReadOnly)
	uint8 Quest;

	UPROPERTY(BlueprintReadOnly)
	bool bHasLifeSteal;
	UPROPERTY(BlueprintReadOnly)
	bool bHasLockEntity;
	UPROPERTY(BlueprintReadOnly)
	bool bHasPuppetry;
	
	UPROPERTY()
	TArray<FString> HitCheckpoint;
	
	

};
