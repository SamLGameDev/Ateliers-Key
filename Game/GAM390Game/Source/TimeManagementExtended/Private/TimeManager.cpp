// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeManager.h"
#include "TimeDialationToken.h"

float UTimeManager::CurrentTimeDialation = 1;
TArray<UTimeDialationToken*> UTimeManager::CurrentDialations;

//to do : rework this so inital start delay works, as currently it sets the Current dialation first

UTimeDialationToken* UTimeManager::SetTimeDialation(const UObject* WorldContextObject, const float InTime, const float LifeTime, const float InitialStartDelay)
{
	UTimeDialationToken* token = NewObject<UTimeDialationToken>(WorldContextObject->GetWorld());
	CurrentDialations.Add(token);
	token->Initialise(InTime, LifeTime, InitialStartDelay);
	CurrentDialations.Sort();

	return token;
}

void UTimeManager::RemoveToken(UTimeDialationToken* Token)
{
	CurrentDialations.Remove(Token);
	CurrentDialations.Sort();

	if (CurrentDialations.IsEmpty())
	{
		CurrentTimeDialation = GetWorldSettings(Token)->SetTimeDilation(1);
		return;
	}

	for (int i = 0; i < CurrentDialations.Num(); i++)
	{
		if (CurrentDialations[i]->IsCurrentlyDelayed())
		{
			continue;
		}
		CurrentTimeDialation = 99999;
		CurrentTimeDialation = SetTokenActive(CurrentDialations[i]);
		break;
	}
}

const float UTimeManager::SetTokenActive(UTimeDialationToken* Token)
{
	if (CurrentTimeDialation > Token->GetDialation())
	{
		CurrentTimeDialation = GetWorldSettings(Token)->SetTimeDilation(Token->GetDialation());
		return CurrentTimeDialation;
	}
	return CurrentTimeDialation;
}

AWorldSettings* UTimeManager::GetWorldSettings(const UObject* WorldContextObject)
{
	return WorldContextObject->GetWorld()->GetWorldSettings();
}
