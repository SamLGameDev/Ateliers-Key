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
class QUESTSYSTEM_API UQuestSubsystem : public UWorldSubsystem
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnyQuestStarted, UWholeQuest*, StartedQuest);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnyStageStarted, UQuestStageData*, StartedQuest);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnyObjectiveStarted, UQuestObjectiveData*, StartedQuest);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestReset);
	
	GENERATED_BODY()
public:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void StartQuestAt(UQuestData* QuestToStart);
	void StartQuestAt(uint8 QuestToStart, uint8 QuestStageToStart);

	void NotifyQuestProgress(UQuestObjectiveData* Quest, const uint8& Progress);

	uint8 GetActiveStageIndex() const;
	
	uint8 GetActiveQuestIndex() const;

	uint8 GetStageIndex(TObjectPtr<UQuestStageData> Stage) const;
	uint8 GetStageIndex(TObjectPtr<UQuestObjectiveData> Stage) const;
	uint8 GetQuestIndex(TObjectPtr<UQuestObjectiveData> Quest) const;
	
	FText GetActiveQuestName() const;

	bool AreQuestsActive() const;
	
	void ResetQuestTo(const uint8 QuestToReset, const uint8 QuestStageToReset);
	
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
	
	UPROPERTY(BlueprintAssignable)
	FOnQuestReset OnQuestReset;

	TArray<FQuest*> ActiveQuests;
	
	FQuestStage* ActiveStage = nullptr;
	
	FQuest* ActiveQuest = nullptr;
	
};
