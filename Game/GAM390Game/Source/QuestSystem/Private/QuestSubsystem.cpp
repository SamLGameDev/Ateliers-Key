// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSubsystem.h"

#include "Constraint.h"
#include "GI_Accessibility.h"
#include "HeadMountedDisplayTypes.h"
#include "QuestData.h"
#include "QuestLibrary.h"

void UQuestSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UGI_SanctumSettings* gameInstance = Cast<UGI_SanctumSettings>(GetGameInstance());
	QuestTable = gameInstance->QuestTable;

	checkf(QuestTable, TEXT("Quest table is not set!"));
	
	TArray<FQuest*> Rows;
	QuestTable->GetAllRows("", Rows);
	FQuest* LastQuest = nullptr;
	for (auto* Row : Rows)
	{
		if (LastQuest != nullptr)
		{
			LastQuest->NextQuest = Row;
		}
		LastQuest = Row;
		FQuestStage* LastStage = nullptr;
		for (auto& stage : Row->Stages)
		{
			if (LastStage != nullptr)
			{
				LastStage->NextStage = &stage;
			}
			LastStage = &stage;
			stage.ParentQuest = Row;
			for (auto& objective : stage.Objectives)
			{
				objective.ParentStage = &stage;
				checkf(objective.QuestData, TEXT("Quest data is not set!"));
				objective.QuestData->ParentQuest = objective;
			}
		}
	}
}

void UQuestSubsystem::StartQuestAt(UQuestData* QuestToStart)
{
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

void UQuestSubsystem::NotifyQuestProgress(UQuestData* Quest, const uint8& Progress)
{
	Quest->ParentQuest.TimesCompleted = FMath::Clamp(Quest->ParentQuest.TimesCompleted + Progress, 0, Quest->ParentQuest.Quantity);
	Quest->OnQuestProgress.Broadcast();
	if (Quest->ParentQuest.TimesCompleted < Quest->ParentQuest.Quantity) return;
	
	Quest->OnQuestCompleted.Broadcast();
	Quest->bIsActive = false;

	bool bAllObjectivesComplete = true;
	for (const auto& objective : Quest->ParentQuest.ParentStage->Objectives)
	{
		if (objective.QuestData->bIsActive) bAllObjectivesComplete = false;
	}
	if (!bAllObjectivesComplete) return;

	FQuestStage* ParentStage = Quest->ParentQuest.ParentStage;
	ParentStage->bIsCompleted = true;

	while (ParentStage->bIsCompleted)
	{
		if (ParentStage->NextStage == nullptr)
		{
			FQuest* ParentQuest = ParentStage->ParentQuest;
			ParentQuest->bIsCompleted = true;
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

	for (const auto& objective : ParentStage->Objectives)
	{
		objective.QuestData->bIsActive = true;
	}
	
}

void UQuestSubsystem::StartQuest(const FQuest* Quest, UQuestData* QuestData)
{
	OnAnyQuestStarted.Broadcast(QuestData);
	QuestData->OnQuestStarted.Broadcast();
	QuestData->bIsActive = true;
	
	
}
