// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AtelierSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ATELIERSKEY_API UAtelierSaveGame : public USaveGame
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
	
	UPROPERTY(BlueprintReadWrite)
	int killedEnemies = 0;

	UPROPERTY(BlueprintReadWrite)
	int pickedUpLoreItems = 0;

	UPROPERTY(BlueprintReadWrite)
	int numOfDeaths = 0;
	
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
	
	UPROPERTY(BlueprintReadWrite)
	bool QuickTimePassed = false;
	
	UPROPERTY(BlueprintReadWrite)
	bool HealthBarVisible = false;
	
	UPROPERTY(BlueprintReadWrite)
	bool ShieldBarVisible = false;
	
	UPROPERTY(BlueprintReadWrite)
	bool GunVisible = false;
	
	UPROPERTY(BlueprintReadWrite)
	bool CompassVisible = false;
	
	UPROPERTY(BlueprintReadWrite)
	bool QuestsVisible = false;
	
	UPROPERTY(BlueprintReadWrite)
	bool AbilitiesVisible = false;
	
};