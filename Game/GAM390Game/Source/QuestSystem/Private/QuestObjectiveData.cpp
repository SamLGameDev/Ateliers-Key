// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestObjectiveData.h"
#include "QuestSubsystem.h"

void UQuestObjectiveData::NotifyProgressMade(const uint8 Quantity, UObject* WorldContextObject)
{
	if (!bIsActive) return;

    WorldContextObject->GetWorld()->GetSubsystem<UQuestSubsystem>()->NotifyQuestProgress(this, Quantity);
}
