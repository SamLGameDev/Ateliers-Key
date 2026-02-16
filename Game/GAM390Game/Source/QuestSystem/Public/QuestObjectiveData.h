// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestData.h"
#include "QuestObjectiveData.generated.h"

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQuestObjectiveData : public UQuestData
{
	GENERATED_BODY()
public:
		
	UPROPERTY(BlueprintReadOnly)
	FQuestObjective ParentQuest;
};
