// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestLibrary.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QuestSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQuestSubsystem : public UGameInstanceSubsystem
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnyQuestStarted, UQuestData*, StartedQuest);
	
	GENERATED_BODY()
public:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void StartQuestAt(UQuestData* QuestToStart);

	void NotifyQuestProgress(UQuestData* Quest, const uint8& Progress);
	

protected:

	UPROPERTY()
	TObjectPtr<UDataTable> QuestTable;

	void StartQuest(const FQuest* Quest, UQuestData* QuestData);

	UPROPERTY(BlueprintAssignable)
	FOnAnyQuestStarted OnAnyQuestStarted;

	TArray<FQuest*> ActiveQuests;
	
};
