// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestLibrary.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QuestSubsystem.generated.h"


class UQuestObjectiveData;

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQuestSubsystem : public UGameInstanceSubsystem
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnyQuestStarted, UWholeQuest*, StartedQuest);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnyStageStarted, UQuestStageData*, StartedQuest);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnyObjectiveStarted, UQuestObjectiveData*, StartedQuest);
	
	GENERATED_BODY()
public:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void StartQuestAt(UQuestData* QuestToStart);

	void NotifyQuestProgress(UQuestObjectiveData* Quest, const uint8& Progress);
	

protected:

	UPROPERTY()
	TObjectPtr<UDataTable> QuestTable;

	void StartQuest(FQuest* Quest, UQuestData* QuestData);

	UPROPERTY(BlueprintAssignable)
	FOnAnyQuestStarted OnAnyQuestStarted;


	UPROPERTY(BlueprintAssignable)
	FOnAnyStageStarted OnAnyStageStarted;


	UPROPERTY(BlueprintAssignable)
	FOnAnyObjectiveStarted OnAnyObjectiveStarted;
	
	

	TArray<FQuest*> ActiveQuests;
	
};
