// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestLibrary.h"
#include "QuestData.h"
#include "QuestObjectiveData.h"
#include "WholeQuest.h"
#include "QuestSubsystem.h"

void UQuestLibrary::StartQuestAt(UQuestData* QuestToStart, UObject* WorldContextObject)
{
	if (!QuestToStart) return;
	
	UQuestSubsystem* questSubsystem = WorldContextObject->GetWorld()->GetSubsystem<UQuestSubsystem>();

	questSubsystem->StartQuestAt(QuestToStart);
	
}

void UQuestLibrary::StartQuestAtIndex(const uint8 QuestToStart, const uint8 QuestStageToStart, UObject* WorldContextObject)
{
	UQuestSubsystem* questSubsystem = WorldContextObject->GetWorld()->GetSubsystem<UQuestSubsystem>();

	questSubsystem->StartQuestAt(QuestToStart, QuestStageToStart);
}

FText UQuestLibrary::GetParentQuestName(UQuestObjectiveData* Quest)
{
	return Quest->ParentQuest->ParentStage->ParentQuest->QuestName;
}


FText UQuestLibrary::GetQuestDisplayName(UQuestObjectiveData* QuestData)
{
	const FString name = QuestData->ParentQuest->Name.ToString();
	
	FString counter = "";
	if (QuestData->ParentQuest->Quantity > 0)
	{
		counter = "(" + FString::FromInt(QuestData->ParentQuest->TimesCompleted) + "/" + FString::FromInt(QuestData->ParentQuest->Quantity) + ")";
	}
	return FText::FromString(name + counter);
}

uint8 UQuestLibrary::GetActiveStageIndex(const UObject* WorldContextObject)
{
	const UQuestSubsystem* subsystem = WorldContextObject->GetWorld()->GetSubsystem<UQuestSubsystem>();
	
	return subsystem->GetActiveStageIndex();
}

uint8 UQuestLibrary::GetActiveQuestIndex(const UObject* WorldContextObject)
{
	const UQuestSubsystem* subsystem = WorldContextObject->GetWorld()->GetSubsystem<UQuestSubsystem>();
	
	return subsystem->GetActiveQuestIndex();
}

FText UQuestLibrary::GetQuestName(UWholeQuest* Quest)
{
	return Quest->ParentQuest->QuestName;
}

void UQuestLibrary::ResetQuestTo(const uint8 QuestToReset, const uint8 QuestStageToReset, UObject* WorldContextObject)
{
	UQuestSubsystem* subsystem = WorldContextObject->GetWorld()->GetSubsystem<UQuestSubsystem>();
	subsystem->ResetQuestTo(QuestToReset, QuestStageToReset);
}

uint8 UQuestLibrary::GetStageIndex(UQuestStageData* Stage, UObject* WorldContextObject)
{
	UQuestSubsystem* subsystem = WorldContextObject->GetWorld()->GetSubsystem<UQuestSubsystem>();
	return subsystem->GetStageIndex(Stage);
}

uint8 UQuestLibrary::GetStageIndexFromObjective(UQuestObjectiveData* Stage, UObject* WorldContextObject)
{
	UQuestSubsystem* subsystem = WorldContextObject->GetWorld()->GetSubsystem<UQuestSubsystem>();
	return subsystem->GetStageIndex(Stage);
}

bool UQuestLibrary::AreQuestsActive(UObject* WorldContextObject)
{
	UQuestSubsystem* subsystem = WorldContextObject->GetWorld()->GetSubsystem<UQuestSubsystem>();
	return subsystem->AreQuestsActive();
}
