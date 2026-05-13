// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckPoints/Checkpoint.h"
#include "Damageable.h"
#include "Kismet/GameplayStatics.h"
#include "GI_Accessibility.h"
#include "CheckPoints/AtelierSaveGame.h"
#include "BP_Player.h"
#include "BP_SceneManager.h"
#include "Abilities/LifeSteal.h"
#include "Abilities/LockEntity.h"
#include "Abilities/Puppetry.h"
#include "QuestLibrary.h"
#include "CheckPoints/SaveSubsystem.h"
// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	CollisionZone = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionZone"));

	CollisionZone->SetupAttachment(RootComponent);

	CollisionZone->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::SetAsCurrentCheckpoint);
}

void ACheckpoint::SetAsCurrentCheckpoint(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABP_Player* player = Cast<ABP_Player>(OtherActor);

	if (!player) return;
	
	USaveSubsystem* sSubsystem = GetWorld()->GetSubsystem<USaveSubsystem>();
	
	UAtelierSaveGame* save = sSubsystem->GetSaveGame();
	
	if (CVarSavingEnabled.GetValueOnAnyThread() == 1 && save->HitCheckpoint.Contains(GetName()) && save->HitCheckpoint.Last() != GetName()) return;
	
	if (OtherActor->Implements<UDamageable>())
	{
		FCheckpointInfo& checkpoint = sSubsystem->CurrentCheckpoint;
		checkpoint.RestartLocation = GetActorLocation();
		checkpoint.RestartRotation = GetActorRotation();
		checkpoint.CombatEncounters = {CombatEncounter};
		
		if (save && save->HitCheckpoint.Contains(GetName()))
		{
			checkpoint.CheckpointQuest = save->Quest;
			checkpoint.CheckpointQuestStage = save->QuestStage;
		}
		else
		{
			checkpoint.CheckpointQuest = UQuestLibrary::GetActiveQuestIndex(this);
			checkpoint.CheckpointQuestStage = UQuestLibrary::GetActiveStageIndex(this);
		}

		if (!GetWorld()->GetStreamingLevels().Contains(CombatEncounter))
		{
			UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, CombatEncounter, true, true, {});
			//UBP_SceneManager::FlushLevelStreamingFull(this);
		}
		
		for (const auto& weapon : player->EquipedWeapons)
		{
			if (weapon->ActorHasTag("AssaultRifle"))
			{
				checkpoint.bHasAssultRifle = true;
				continue;
			}
			if (weapon->ActorHasTag("SniperRifle"))
			{
				checkpoint.bHasSniper = true;
				continue;
			}
			if (weapon->ActorHasTag("Shotgun"))
			{
				checkpoint.bHasShotgun = true;
				continue;
			}
		}

		checkpoint.WorldsToLoad.Empty();
		
		for (const auto& world : WorldsToLoad)
		{
			checkpoint.WorldsToLoad.Add(world->GetName());
		}
		if (CVarSavingEnabled.GetValueOnAnyThread() == 0) return;
		SaveToSlot(player);
		Destroy();
	}
}

void ACheckpoint::SaveToSlot(ABP_Player* Player)
{
	if (CVarSavingEnabled.GetValueOnAnyThread() == 0) return;
	USaveSubsystem* sSubsystem = GetWorld()->GetSubsystem<USaveSubsystem>();
	
	UAtelierSaveGame* save = sSubsystem->GetSaveGame();
	
	
	if (save->HitCheckpoint.Contains(GetName())) return;


	save->BaseMap = GetWorld()->GetName();
	save->CombatEncounters.Empty();

	FString levelName = CombatEncounter.GetAssetName();
	
	if (!levelName.IsEmpty()) save->CombatEncounters.Add(CombatEncounter);
	
	save->WorldsToLoad.Empty();
	
	for (const auto& world : WorldsToLoad)
	{
		save->WorldsToLoad.Add(world->GetName());
	}
	save->RestartLocation = GetActorLocation();

	save->RestartRotation = GetActorRotation();

	for (const auto& weapon : Player->EquipedWeapons)
	{
		if (weapon->ActorHasTag("AssaultRifle"))
		{
			save->bHasAssultRifle = true;
			continue;
		}
		if (weapon->ActorHasTag("SniperRifle"))
		{
			save->bHasSniper = true;
			continue;
		}
		if (weapon->ActorHasTag("Shotgun"))
		{
			save->bHasShotgun = true;
			continue;
		}
	}

	for (const auto& ability : Player->UnlockedAbilities)
	{
		if (ability->IsA(ULifeSteal::StaticClass()))
		{
			save->bHasLifeSteal = true;
			continue;
		};
		if (ability->IsA(ULockEntity::StaticClass()))
		{
			save->bHasLockEntity = true;
			continue;
		};
		if (ability->IsA(UPuppetry::StaticClass()))
		{
			save->bHasPuppetry = true;
			continue;
		};
	}
	
	save->QuestStage = sSubsystem->CurrentCheckpoint.CheckpointQuestStage;
	save->Quest = sSubsystem->CurrentCheckpoint.CheckpointQuest;
	
	save->HitCheckpoint.Add(GetName());
	
	GetWorld()->GetSubsystem<USaveSubsystem>()->OnCheckpointSave.Broadcast();
	TObjectPtr<UGI_SanctumSettings> gameInstance = Cast<UGI_SanctumSettings>(GetWorld()->GetGameInstance());
	const FString& slotName = gameInstance->GetSaveSlot();
	
	

	UGameplayStatics::AsyncSaveGameToSlot(save, slotName, 0);
	
	
}
