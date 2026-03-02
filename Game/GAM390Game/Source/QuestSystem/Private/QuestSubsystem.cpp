// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSubsystem.h"

#include "Constraint.h"
#include "GI_Accessibility.h"
#include "IPropertyTable.h"
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
	
	UGI_SanctumSettings* gameInstance = Cast<UGI_SanctumSettings>(GetWorld()->GetGameInstance());
	if (gameInstance == nullptr) return;
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

void UQuestSubsystem::StartQuestAt(const uint8 QuestToStart, const uint8 QuestStageToStart)
{
	if (CVarQuestEnabled.GetValueOnAnyThread() == 0) return;
	TArray<FQuest*> Rows;
	QuestTable->GetAllRows("", Rows);
	
	StartQuest(Rows[QuestToStart], Rows[QuestToStart]->Stages[QuestStageToStart].QuestData);
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
			//checkf(ParentQuest->Stages.IsEmpty(), TEXT("Quest has no stages, either add some or remove it"))

			OnAnyQuestStarted.Broadcast(ParentQuest->QuestData);
			ParentStage = &ParentQuest->Stages[0];
			ActiveQuest = ParentQuest;
		}

		if (ParentStage->NextStage == nullptr) break;
		
		ParentStage = ParentStage->NextStage;
	}
	
			
	OnAnyStageStarted.Broadcast(ParentStage->QuestData);
	ParentStage->QuestData->OnQuestStarted.Broadcast();
	ParentStage->QuestData->bIsActive = true;
	ActiveStage = ParentStage;

	for (const auto& objective : ParentStage->Objectives)
	{
		if (objective.bIsCompleted) continue;
		
		objective.QuestData->bIsActive = true;
		OnAnyObjectiveStarted.Broadcast(objective.QuestData);
		objective.QuestData->OnQuestStarted.Broadcast();
	}
	
}

uint8 UQuestSubsystem::GetActiveStageIndex() const
{
	TArray<FQuest*> Rows;
	QuestTable->GetAllRows("", Rows);
	for (auto* Row : Rows)
	{
		for (uint8 i = 0 ; i < Row->Stages.Num(); i++)
		{
			FQuestStage* stage = &Row->Stages[i];
			if (stage->QuestData == ActiveStage->QuestData)
			{
				return i;
			}
		}
	}
	return 0;
}

uint8 UQuestSubsystem::GetActiveQuestIndex() const
{
	TArray<FQuest*> Rows;
	QuestTable->GetAllRows("", Rows);
	for (uint8 i = 0; i < Rows.Num(); i++)
	{
		if (Rows[i]->QuestData == ActiveQuest->QuestData) return i; 
	}
	return 0;
}

uint8 UQuestSubsystem::GetStageIndex(TObjectPtr<UQuestStageData> Stage) const
{
	TArray<FQuest*> Rows;
	QuestTable->GetAllRows("", Rows);
	for (auto* Row : Rows)
	{
		for (uint8 i = 0 ; i < Row->Stages.Num(); i++)
		{
			FQuestStage* stage = &Row->Stages[i];
			if (stage->QuestData == Stage)
			{
				return i;
			}
		}
	}
	return 0;
}

uint8 UQuestSubsystem::GetStageIndex(TObjectPtr<UQuestObjectiveData> Stage) const
{
	TArray<FQuest*> Rows;
	QuestTable->GetAllRows("", Rows);
	for (auto* Row : Rows)
	{
		for (uint8 i = 0 ; i < Row->Stages.Num(); i++)
		{
			FQuestStage* stage = &Row->Stages[i];
			if (stage->QuestData == Stage->ParentQuest->ParentStage->QuestData)
			{
				return i;
			}
		}
	}
	return 0;
}

uint8 UQuestSubsystem::GetQuestIndex(TObjectPtr<UQuestObjectiveData> Quest) const
{
	TArray<FQuest*> Rows;
	QuestTable->GetAllRows("", Rows);
	for (uint8 rowNum = 0; rowNum < Rows.Num(); rowNum++)
	{
		const auto& row = Rows[rowNum];
		for (uint8 i = 0 ; i < row->Stages.Num(); i++)
		{
			FQuestStage* stage = &row->Stages[i];
			if (stage->QuestData == Quest->ParentQuest->ParentStage->QuestData)
			{
				return rowNum;
			}
		}
	}
	return 0;
}

bool UQuestSubsystem::AreQuestsActive() const
{
	return ActiveStage != nullptr;
}

void UQuestSubsystem::ResetQuestTo(const uint8 QuestToReset, const uint8 QuestStageToReset)
{
	TArray<FQuest*> Rows;
	QuestTable->GetAllRows("", Rows);
	for (uint8 ActiveQuestIndex = GetActiveQuestIndex(); ActiveQuestIndex != QuestToReset; ActiveQuestIndex--)
	{
		FQuest* quest = Rows[ActiveQuestIndex];
		quest->bIsCompleted = false;
		quest->QuestData->bIsActive = false;
		
		for (uint8 i = 0; i < quest->Stages.Num(); i++)
		{
			FQuestStage* stage = &quest->Stages[i];
			stage->bIsCompleted = false;
			stage->QuestData->bIsActive = false;
			for (uint8 j = 0; j < stage->Objectives.Num(); j++)
			{
				FQuestObjective* objective = &stage->Objectives[j];
				objective->bIsCompleted = false;
				if (objective->bIsAlwaysActive) objective->QuestData->bIsActive = true;
				else objective->QuestData->bIsActive = false;
				
				objective->TimesCompleted = 0;
			}
		}
	}
	
	for (uint8 ActiveStageIndex = GetActiveStageIndex(); ActiveStageIndex != QuestStageToReset; ActiveStageIndex--)
	{
		FQuestStage* stage = &Rows[QuestToReset]->Stages[ActiveStageIndex];
		stage->bIsCompleted = false;
		stage->QuestData->bIsActive = false;
		for (uint8 i = 0; i < stage->Objectives.Num(); i++)
		{
			FQuestObjective* objective = &stage->Objectives[i];
			objective->bIsCompleted = false;
			if (objective->bIsAlwaysActive) objective->QuestData->bIsActive = true;
			else objective->QuestData->bIsActive = false;
				
			objective->TimesCompleted = 0;
		}
	}
	FQuestStage* stage = &Rows[QuestToReset]->Stages[QuestStageToReset];
	stage->bIsCompleted = false;
	stage->QuestData->bIsActive = false;
	for (uint8 i = 0; i < stage->Objectives.Num(); i++)
	{
		FQuestObjective* objective = &stage->Objectives[i];
		objective->bIsCompleted = false;
		if (objective->bIsAlwaysActive) objective->QuestData->bIsActive = true;
		else objective->QuestData->bIsActive = false;
				
		objective->TimesCompleted = 0;
	}
	OnQuestReset.Broadcast();
	StartQuest(Rows[QuestToReset], stage->QuestData);

}

void UQuestSubsystem::StartQuest(FQuest* Quest, UQuestData* QuestData)
{
	OnAnyQuestStarted.Broadcast(Quest->QuestData);
	QuestData->OnQuestStarted.Broadcast();
	QuestData->bIsActive = true;
	
	ActiveQuest = Quest;
	
	for (auto& stage : Quest->Stages)
	{
		if (stage.QuestData != QuestData)
		{
			stage.bIsCompleted = true;
			continue;
		}
		
		if (stage.bIsCompleted) continue;

		OnAnyStageStarted.Broadcast(stage.QuestData);
		stage.QuestData->OnQuestStarted.Broadcast();
		stage.QuestData->bIsActive = true;
		
		ActiveStage = &stage;
		
		for (const auto& objective : stage.Objectives)
		{
			objective.QuestData->bIsActive = true;
			OnAnyObjectiveStarted.Broadcast(objective.QuestData);
			objective.QuestData->OnQuestStarted.Broadcast();
		}
		return;
		
	}
}
