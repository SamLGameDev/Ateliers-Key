// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckPoints/Checkpoint.h"
#include "Damageable.h"
#include "Kismet/GameplayStatics.h"
#include "GI_Accessibility.h"
#include "CheckPoints/AtelierSaveGame.h"
#include "BP_Player.h"
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
	if (OtherActor->Implements<UDamageable>())
	{
		FCheckpointInfo checkpoint;
		checkpoint.RestartLocation = GetActorLocation();
		checkpoint.RestartRotation = GetActorRotation();
		checkpoint.CombatEncounters = {CombatEncounter};

		if (NextCheckpoint)
		{
			checkpoint.CombatEncounters.Add(NextCheckpoint->CombatEncounter);
			UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, NextCheckpoint->CombatEncounter, true, false, {});

		}

		if (!GetWorld()->GetStreamingLevels().Contains(CombatEncounter))
		{
			UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, CombatEncounter, true, false, {});
		}

		CurrentCheckpoint->SetObject(checkpoint);


		Destroy();
	}
}

void ACheckpoint::SaveToSlot(ABP_Player* Player)
{
	UGI_SanctumSettings* gInstance =  Cast<UGI_SanctumSettings>(GetGameInstance());

	const FString& slotName = gInstance->GetSaveSlot();

	UAtelierSaveGame* save = Cast<UAtelierSaveGame>(UGameplayStatics::CreateSaveGameObject(UAtelierSaveGame::StaticClass()));

	save->BaseMap = GetWorld()->GetName();

	save->CombatEncounters = { CombatEncounter->GetName(), NextCheckpoint->CombatEncounter->GetName() };

	save->RestartLocation = GetActorLocation();

	save->RestartRotation = GetActorRotation();

	//Player->EquipedWeapons.                                                    

}
