// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestData.h"
#include "QuestLibrary.h"

#include "QuestSubsystem.h"

void UQuestData::NotifyProgressMade(const uint8 Quantity, UObject* WorldContextObject)
{
	if (!bIsActive) return;
	
	WorldContextObject->GetWorld()->GetGameInstance()->GetSubsystem<UQuestSubsystem>()->NotifyQuestProgress(this, Quantity);
}
