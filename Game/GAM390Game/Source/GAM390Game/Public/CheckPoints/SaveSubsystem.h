// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SaveSubsystem.generated.h"

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
	
	UPROPERTY(BlueprintAssignable)
	FOnCheckpointSave OnCheckpointSave;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCheckpointLoad OnCheckpointLoad;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCheckpointLoad OnCheckpointRestart;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAtelierSaveGame> LoadedSave = nullptr;
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<TSoftObjectPtr<UWorld>> GetLoadedCombatEncounters();
	
};
