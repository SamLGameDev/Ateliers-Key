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

	UFUNCTION(BlueprintCallable, Category = "SceneManager|Level Loading")
	ULevelLoadWaitToken* WaitUntilLevelsAreVisible(const TArray<FName>& Levels);
protected:

	UFUNCTION()
	void WaitForLevelsToBeLoaded(const TArray<FName>& Levels, ULevelLoadWaitToken* Token);

	
	UFUNCTION()
	void SignalLevelsLoaded(ULevelLoadWaitToken* Token);

	static constexpr float LevelsLoadedCheckRate = 0.5f;

	void ScheduleLevelLoadedCheck(const TArray<FName>& Levels, ULevelLoadWaitToken* Token);

	UPROPERTY()
	TArray<ULevelLoadWaitToken*> CurrentWaitTokens;

};
