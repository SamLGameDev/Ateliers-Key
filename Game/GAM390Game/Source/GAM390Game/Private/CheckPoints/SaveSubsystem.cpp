// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPoints/SaveSubsystem.h"

#include "GI_Accessibility.h"
#include "CheckPoints/CheckpointSaveRules.h"
#include "Kismet/GameplayStatics.h"
#include "CheckPoints/AtelierSaveGame.h"

FString USaveSubsystem::CurrentSaveSlot = "Save0";

void USaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	if (CVarSavingEnabled.GetValueOnAnyThread() == 0) return;
	
	const FString& slotName = GetSaveSlot();
	
	if (UGameplayStatics::DoesSaveGameExist(slotName, 0))
	{
		LoadedSave = Cast<UAtelierSaveGame>(UGameplayStatics::LoadGameFromSlot(slotName, 0));
	}
	
	OnCheckpointLoad.Broadcast();
}

UAtelierSaveGame* USaveSubsystem::GetSaveGame()
{
	if (LoadedSave) return LoadedSave;
	
	const FString& slotName = GetSaveSlot();
	if (UGameplayStatics::DoesSaveGameExist(slotName, 0))
	{
		LoadedSave = Cast<UAtelierSaveGame>(UGameplayStatics::LoadGameFromSlot(slotName, 0));
	}
	else
	{
		LoadedSave = Cast<UAtelierSaveGame>(UGameplayStatics::CreateSaveGameObject(UAtelierSaveGame::StaticClass()));
	}
	return LoadedSave;
}

void USaveSubsystem::SetSaveSlot(const FString& SlotName)
{
	CurrentSaveSlot = SlotName;
	UAtelierSaveGame* save = GetSaveGame();
	UGI_SanctumSettings* gi =  Cast<UGI_SanctumSettings>(GetWorld()->GetGameInstance());
	gi->EnemyKills = save->killedEnemies;
}

FString USaveSubsystem::GetSaveSlot()
{
	return CVarSavingEnabled.GetValueOnAnyThread() == 1 ? CurrentSaveSlot : "SavingDisabled";
}

void USaveSubsystem::DeleteSaveSlot(const uint8& Slot)
{
	UGameplayStatics::DeleteGameInSlot(UCheckpointSaveRules::MakeSaveSlotName(Slot), 0);
	LoadedSave = nullptr;
}
