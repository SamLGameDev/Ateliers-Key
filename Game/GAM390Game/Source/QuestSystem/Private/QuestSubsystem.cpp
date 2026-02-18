// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSubsystem.h"

#include "Constraint.h"
#include "GI_Accessibility.h"
#include "QuestData.h"
#include "QuestObjectiveData.h"
#include "WholeQuest.h"
#include "QuestLibrary.h"
#include "QuestStageData.h"

static TAutoConsoleVariable<int32> CVarQuestEnabled(
	TEXT("QuestSystem.Enabled"),
	1,
	TEXT("Disable the quest system = 0, Enable = 1"),
	ECVF_Default);

void UQuestSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (CVarQuestEnabled.GetValueOnAnyThread() == 0) return;
	
	UGI_SanctumSettings* gameInstance = Cast<UGI_SanctumSettings>(GetGameInstance());
	QuestTable = gameInstance->QuestTable;

	checkf(QuestTable, TEXT("Quest table is not set!"));
	
	TArray<FQuest*> Rows;
	QuestTable->GetAllRows("", Rows);
	FQuest* LastQuest = nullptr;
	for (auto* Row : Rows)
	{
		Row->QuestData->ParentQuest = Row;
		Row->bIsCompleted = false;
		if (LastQuest != nullptr)
		{
			LastQuest->NextQuest = Row;
		}
		LastQuest = Row;
		FQuestStage* LastStage = nullptr;
		for (auto& stage : Row->Stages)
		{
			stage.bIsCompleted = false;
			if (LastStage != nullptr)
			{
				LastStage->NextStage = &stage;
			}
			LastStage = &stage;
			stage.ParentQuest = Row;
			for (auto& objective : stage.Objectives)
			{
				if (objective.bIsAlwaysActive)
				{
					objective.QuestData->bIsActive = true;
				}
				objective.bIsCompleted = false;
				
				objective.TimesCompleted = 0;
				objective.ParentStage = &stage;
				checkf(objective.QuestData, TEXT("Quest data is not set!"));
				objective.QuestData->ParentQuest = &objective;
			}
		}
	}
}

void UQuestSubsystem::StartQuestAt(UQuestData* QuestToStart)
{
	if (CVarQuestEnabled.GetValueOnAnyThread() == 0) return;
	TArray<FQuest*> Rows;
	QuestTable->GetAllRows("", Rows);
	
	for (auto* Row : Rows)
	{
		for (auto& stage : Row->Stages)
		{
			for (auto& objective : stage.Objectives)
			{
				if (objective.QuestData == QuestToStart)
				{
					StartQuest(Row, objective.QuestData);
				}
			}
		}
	}

}

void UQuestSubsystem::NotifyQuestProgress(UQuestObjectiveData* Quest, const uint8& Progress)
{
	if (CVarQuestEnabled.GetValueOnAnyThread() == 0) return;
	Quest->ParentQuest->TimesCompleted = FMath::Clamp(Quest->ParentQuest->TimesCompleted + Progress, 0, Quest->ParentQuest->Quantity);
	Quest->OnQuestProgress.Broadcast();
	if (Quest->ParentQuest->TimesCompleted < Quest->ParentQuest->Quantity) return;
	
	Quest->OnQuestCompleted.Broadcast(Quest);
	Quest->bIsActive = false;
	Quest->ParentQuest->bIsCompleted = true;
	bool bAllObjectivesComplete = true;
	for (const auto& objective : Quest->ParentQuest->ParentStage->Objectives)
	{
		if (!objective.bIsCompleted && !objective.bIsOptional) bAllObjectivesComplete = false;
	}
	if (!bAllObjectivesComplete) return;

	FQuestStage* ParentStage = Quest->ParentQuest->ParentStage;
	ParentStage->bIsCompleted = true;

	if (!ParentStage->QuestData->bIsActive) return;
	ParentStage->QuestData->bIsActive = false;
	while (ParentStage->bIsCompleted)
	{
		ParentStage->QuestData->OnQuestCompleted.Broadcast(ParentStage->QuestData);
		if (ParentStage->NextStage == nullptr)
		{
			FQuest* ParentQuest = ParentStage->ParentQuest;
			ParentQuest->bIsCompleted = true;
			ParentQuest->QuestData->OnQuestCompleted.Broadcast(ParentQuest->QuestData);
			while (ParentQuest->bIsCompleted)
			{
				if (ParentQuest->NextQuest == nullptr) return;
				ParentQuest = ParentQuest->NextQuest;
			}

			checkf(ParentQuest->Stages.IsEmpty(), TEXT("Quest has no stages, either add some or remove it")) 
			ParentStage = &ParentQuest->Stages[0];
		}
		
		ParentStage = ParentStage->NextStage;
	}
	
			
	OnAnyStageStarted.Broadcast(ParentStage->QuestData);
	ParentStage->QuestData->OnQuestStarted.Broadcast();
	ParentStage->QuestData->bIsActive = true;

	for (const auto& objective : ParentStage->Objectives)
	{
		if (objective.bIsCompleted) continue;
		
		objective.QuestData->bIsActive = true;
		OnAnyObjectiveStarted.Broadcast(objective.QuestData);
		objective.QuestData->OnQuestStarted.Broadcast();
	}
	
}

void UQuestSubsystem::StartQuest(FQuest* Quest, UQuestData* QuestData)
{
	OnAnyQuestStarted.Broadcast(Quest->QuestData);
	QuestData->OnQuestStarted.Broadcast();
	QuestData->bIsActive = true;
	for (auto& stage : Quest->Stages)
	{
		if (stage.bIsCompleted) continue;

		OnAnyStageStarted.Broadcast(stage.QuestData);
		stage.QuestData->OnQuestStarted.Broadcast();
		stage.QuestData->bIsActive = true;
		
		for (const auto& objective : stage.Objectives)
		{
			objective.QuestData->bIsActive = true;
			OnAnyObjectiveStarted.Broadcast(objective.QuestData);
			objective.QuestData->OnQuestStarted.Broadcast();
		}
		return;
		
	}
}
