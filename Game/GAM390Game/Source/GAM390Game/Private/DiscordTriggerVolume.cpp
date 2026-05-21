// Fill out your copyright notice in the Description page of Project Settings.

#include "DiscordTriggerVolume.h"

#include "BP_Player.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GI_Accessibility.h"
#include "Kismet/GameplayStatics.h"

ADiscordTriggerVolume::ADiscordTriggerVolume()
{
    PrimaryActorTick.bCanEverTick = false;

    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    SetRootComponent(Box);

    Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Box->SetCollisionObjectType(ECC_WorldStatic);
    Box->SetCollisionResponseToAllChannels(ECR_Ignore);
    Box->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void ADiscordTriggerVolume::BeginPlay()
{
    Super::BeginPlay();

    if (Box)
    {
        Box->OnComponentBeginOverlap.AddDynamic(
            this,
            &ADiscordTriggerVolume::OnOverlapBegin
        );
    }

    // Check for players already inside the volume after spawn
    FTimerHandle CheckHandle;
    GetWorld()->GetTimerManager().SetTimer(
        CheckHandle,
        [this]()
        {
            TArray<AActor*> OverlappingActors;
            Box->GetOverlappingActors(OverlappingActors, ACharacter::StaticClass());

            for (AActor* Actor : OverlappingActors)
            {
                if (Cast<ACharacter>(Actor))
                {
                    UpdatePresence();
                    return;
                }
            }
        },
        0.2f,
        false
    );
}

void ADiscordTriggerVolume::UpdatePresence()
{
    UGI_SanctumSettings* GI = Cast<UGI_SanctumSettings>(
        UGameplayStatics::GetGameInstance(this)
    );

    if (!GI)
    {
        UE_LOG(LogTemp, Warning, TEXT("DiscordTriggerVolume: Could not get game instance"));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("Discord presence updated: %s"), *Details);
    GI->SetDiscordPresenceDetailsOnly(Details);
}

void ADiscordTriggerVolume::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    if (!OtherActor || !Cast<ABP_Player>(OtherActor))
        return;

    UpdatePresence();
}