// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestLibrary.h"
#include "QuestData.h"
#include "QuestObjectiveData.h"
#include "WholeQuest.h"
#include "QuestSubsystem.h"

void UQuestLibrary::StartQuestAt(UQuestData* QuestToStart, UObject* WorldContextObject)
{
	if (!QuestToStart) return;
	
	UQuestSubsystem* questSubsystem = WorldContextObject->GetWorld()->GetGameInstance()->GetSubsystem<UQuestSubsystem>();

	questSubsystem->StartQuestAt(QuestToStart);
	
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

FText UQuestLibrary::GetQuestName(UWholeQuest* Quest)
{
	return Quest->ParentQuest->QuestName;
}
