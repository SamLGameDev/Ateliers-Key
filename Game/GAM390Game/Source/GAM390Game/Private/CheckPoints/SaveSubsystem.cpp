// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPoints/SaveSubsystem.h"

#include "GI_Accessibility.h"
#include "CheckPoints/CheckpointSaveRules.h"
#include "Kismet/GameplayStatics.h"
#include "CheckPoints/AtelierSaveGame.h"

void USaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	TObjectPtr<UGI_SanctumSettings> gameInstance = Cast<UGI_SanctumSettings>(GetWorld()->GetGameInstance());
	
	if (!gameInstance) return;
	
	const FString& slotName = gameInstance->GetSaveSlot();
	
	if (UGameplayStatics::DoesSaveGameExist(slotName, 0))
	{
		LoadedSave = Cast<UAtelierSaveGame>(UGameplayStatics::LoadGameFromSlot(slotName, 0));
	}
	
	OnCheckpointLoad.Broadcast();
}

TArray<TSoftObjectPtr<UWorld>> USaveSubsystem::GetLoadedCombatEncounters()
{
	TArray<TSoftObjectPtr<UWorld>> LoadedCombatEncounters;
	
	if (!LoadedSave) return LoadedCombatEncounters;
	
	for (const auto& levelName : LoadedSave->CombatEncounters)
	{
		TSoftObjectPtr<UWorld> WorldAsset = TSoftObjectPtr<UWorld>(
			FSoftObjectPath(levelName)
		);
		LoadedCombatEncounters.Add(WorldAsset);
	}
	return LoadedCombatEncounters;
	
	
}
