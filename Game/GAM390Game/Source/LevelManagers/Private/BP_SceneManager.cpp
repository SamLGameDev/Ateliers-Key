// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_SceneManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void UBP_SceneManager::FlushLevelStreamingFull(UObject* WorldContextObject)
{
	WorldContextObject->GetWorld()->BlockTillLevelStreamingCompleted();
}

TArray<UObject*> UBP_SceneManager::ObjectsWithTimers;

void UBP_SceneManager::Quit(UObject* WorldContextObject, APlayerController* Controller)
{
	UKismetSystemLibrary::QuitGame(WorldContextObject, Controller, EQuitPreference::Quit, true);
}

void UBP_SceneManager::ReloadLevel(UObject* WorldContextObject)
{
	LoadLevel(WorldContextObject->GetWorld()->GetFName(), WorldContextObject);
}

void UBP_SceneManager::LoadLevel(FName Level, UObject* WorldContextObject)
{

	ClearAllTimers(WorldContextObject);
	UGameplayStatics::OpenLevel(WorldContextObject, Level, true);
}


void UBP_SceneManager::ClearAllTimers(UObject* WorldContextObject)
{
	for (UObject* Object : ObjectsWithTimers) {
		WorldContextObject->GetWorld()->GetTimerManager().ClearAllTimersForObject(Object);
	}
}
