// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestData.h"
#include "QuestObjectiveData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class QUESTSYSTEM_API UQuestObjectiveData : public UQuestData
{
	GENERATED_BODY()
public:
	FQuestObjective* ParentQuest;

	UFUNCTION(BlueprintCallable)
	void NotifyProgressMade(const uint8 Quantity, UObject* WorldContextObject);

};
