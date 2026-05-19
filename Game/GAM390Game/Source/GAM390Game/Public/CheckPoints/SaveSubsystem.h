// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseVariableStore.h"
#include "Subsystems/WorldSubsystem.h"
#include "SaveSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FCheckpointInfo
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite)
	FVector RestartLocation;

	UPROPERTY(BlueprintReadWrite)
	FRotator RestartRotation;

	UPROPERTY(BlueprintReadWrite)
	TArray<TSoftObjectPtr<UWorld>> CombatEncounters;
	
	UPROPERTY(BlueprintReadWrite)
	uint8 CheckpointQuest;
	UPROPERTY(BlueprintReadWrite)
	uint8 CheckpointQuestStage;

	UPROPERTY(BlueprintReadWrite)
	bool bHasAssultRifle = false;
	UPROPERTY(BlueprintReadWrite)
	bool bHasShotgun = false;
	UPROPERTY(BlueprintReadWrite)
	bool bHasSniper = false;

	UPROPERTY(BlueprintReadWrite)
	int killedEnemies;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> WorldsToLoad;
};

class UAtelierSaveGame;
/**
 * 
 */
UCLASS()
class GAM390GAME_API USaveSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckpointSave);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckpointLoad);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckpointRestart);
	
	UFUNCTION(BlueprintCallable)
	UAtelierSaveGame* GetSaveGame();

	UFUNCTION(BlueprintCallable, Category = "Save")
	void AddToKilledEnemies(int32 Amount);
	
	UPROPERTY(BlueprintAssignable)
	FOnCheckpointSave OnCheckpointSave;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCheckpointLoad OnCheckpointLoad;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCheckpointLoad OnCheckpointRestart;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAtelierSaveGame> LoadedSave = nullptr;

	UPROPERTY(BlueprintReadWrite)
	FCheckpointInfo CurrentCheckpoint;

};