// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestLibrary.h"
#include "QuestData.h"
#include "QuestSubsystem.h"

void UQuestLibrary::StartQuestAt(UQuestData* QuestToStart, UObject* WorldContextObject)
{
	if (!QuestToStart) return;
	
	UQuestSubsystem* questSubsystem = WorldContextObject->GetWorld()->GetGameInstance()->GetSubsystem<UQuestSubsystem>();

	questSubsystem->StartQuestAt(QuestToStart);
	
}

FText UQuestLibrary::GetParentQuestName(UQuestData* Quest)
{
	return Quest->ParentQuest.ParentStage->ParentQuest->QuestName;
}


FText UQuestLibrary::GetQuestDisplayName(UQuestData* QuestData)
{
	const FString name = QuestData->ParentQuest.Name.ToString();
	const FString counter = "(" + FString::FromInt(QuestData->ParentQuest.TimesCompleted) + "/" + FString::FromInt(QuestData->ParentQuest.Quantity) + ")";
	return FText::FromString(name + counter);
}
