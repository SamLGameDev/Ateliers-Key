// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LevelManagerSubsystem.generated.h"


UCLASS(Blueprintable, BlueprintType, Category = "Level Managers")
class ULevelLoadWaitToken : public UObject
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComplete);
	GENERATED_BODY()
	public:

	UPROPERTY(BlueprintAssignable, Category = "Level Managers")
	FOnComplete OnComplete;
};

/**
 * 
 */
UCLASS()
class LEVELMANAGERS_API ULevelManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	public:

	/**
 * Reloads level stream levels, by unloading and reloading. DOES NOT WORK WITH LEVELS BOUND TO STREAMING VOLUMES
 * @param Levels
 * Levels to load
 * @return Token to subscribe to the onCompletion event
 */
	UFUNCTION(BlueprintCallable, Category = "SceneManager|Level Loading")
	ULevelLoadWaitToken* ReloadLevels(const TArray<TSoftObjectPtr<UWorld>>& Levels);

	UFUNCTION(BlueprintCallable, Category = "SceneManager|Level Loading")
	ULevelLoadWaitToken* WaitUntilLevelsAreVisible(const TArray<FName>& Levels);
	
protected:
	
	UFUNCTION()
	void UnloadLevels(const TArray<TSoftObjectPtr<UWorld>>& Levels, ULevelLoadWaitToken* Token);

	UFUNCTION()
	void LoadLevels(const TArray<TSoftObjectPtr<UWorld>>& Levels, ULevelLoadWaitToken* Token);
	
	UFUNCTION()
	void WaitForLevelsToBeLoaded(const TArray<FName>& Levels, ULevelLoadWaitToken* Token);
	
	UFUNCTION()
	void SignalLevelsLoaded(ULevelLoadWaitToken* Token);

	static constexpr float LevelsLoadedCheckRate = 0.1f;

	static constexpr float LevelsUnloadedCheckRate = 0.1f;

	void ScheduleLevelsUnloadedCheck(const TArray<TSoftObjectPtr<UWorld>>& Levels, ULevelLoadWaitToken* Token);
	void ScheduleLevelsLoadedCheck(const TArray<TSoftObjectPtr<UWorld>>& Levels, ULevelLoadWaitToken* Token);
	void ScheduleLevelLoadedCheck(const TArray<FName>& Levels, ULevelLoadWaitToken* Token);

	UPROPERTY()
	TArray<ULevelLoadWaitToken*> CurrentTokens;

};
