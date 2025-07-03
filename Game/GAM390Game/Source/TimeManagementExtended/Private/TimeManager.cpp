// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeManager.h"
#include "TimeDialationToken.h"

float UTimeManager::CurrentTimeDialation = 1;
TArray<UTimeDialationToken*> UTimeManager::CurrentDialations;

UTimeDialationToken* UTimeManager::SetTimeDialation(const UObject* WorldContextObject, const float InTime, const float LifeTime)
{
	if (CurrentTimeDialation > InTime)
	{
		CurrentTimeDialation = GetWorldSettings(WorldContextObject)->SetTimeDilation(InTime);
	}

	UTimeDialationToken* token = NewObject<UTimeDialationToken>(WorldContextObject->GetWorld());
	CurrentDialations.Add(token);
	token->Initialise(InTime, LifeTime);
	CurrentDialations.Sort();
	return token;
}

void UTimeManager::RemoveToken(UTimeDialationToken* Token)
{
	CurrentDialations.Remove(Token);
	CurrentDialations.Sort();

	CurrentTimeDialation = GetWorldSettings(Token)->SetTimeDilation
	(
		CurrentDialations.IsEmpty() ? 1 : CurrentDialations[0]->GetDialation()
	);
}

AWorldSettings* UTimeManager::GetWorldSettings(const UObject* WorldContextObject)
{
	return WorldContextObject->GetWorld()->GetWorldSettings();
}
