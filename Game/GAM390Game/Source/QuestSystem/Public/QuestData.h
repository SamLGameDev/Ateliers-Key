// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "QuestLibrary.h"
#include "QuestData.generated.h"


/**
 * 
 */
UCLASS(Abstract, NotBlueprintable)
class QUESTSYSTEM_API UQuestData : public UPrimaryDataAsset
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestCompleted, UQuestData*, CompletedQuest);
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

	bool bIsActive = false;
	
};
