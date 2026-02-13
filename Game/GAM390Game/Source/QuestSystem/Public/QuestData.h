// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "QuestLibrary.h"
#include "QuestData.generated.h"
/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQuestData : public UPrimaryDataAsset
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestCompleted);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestStarted);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestProgressMade);
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintAssignable)
	FOnQuestCompleted OnQuestCompleted;
	UPROPERTY(BlueprintAssignable)
	FOnQuestStarted OnQuestStarted;
	UPROPERTY(BlueprintAssignable)
	FOnQuestProgressMade OnQuestProgress;

	UFUNCTION(BlueprintCallable)
	void NotifyProgressMade(const uint8 Quantity, UObject* WorldContextObject);

	bool bIsActive = false;
	
	UPROPERTY(BlueprintReadOnly)
	FQuestObjective ParentQuest;
	
};
