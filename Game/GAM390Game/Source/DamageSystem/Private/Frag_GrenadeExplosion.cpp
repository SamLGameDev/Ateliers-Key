// Fill out your copyright notice in the Description page of Project Settings.


#include "Frag_GrenadeExplosion.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "DamageSystem.h"

void AFrag_GrenadeExplosion::BeginPlay() {
	Super::BeginPlay();

	GetActorsInRadius(this, GetActorLocation(), 320, FoundActors);
}

void AFrag_GrenadeExplosion::GetActorsInRadius(UObject* WorldContext, FVector Origin, float Radius, TArray<AActor*>& OutActors)
{
    UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContext);
    if (!World) return;

    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));

    TArray<AActor*> IgnoredActors;
    TArray<FHitResult> HitResults;

    bool bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(
        WorldContext,
        Origin,
        Origin,
        Radius,
        ObjectTypes,
        false,
        IgnoredActors,
        EDrawDebugTrace::ForDuration,
        HitResults,
        true
    );

    /*if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan,
            FString::Printf(TEXT("Grenade found %d hits"), HitResults.Num()));
    }*/

    for (const FHitResult& Hit : HitResults)
    {
        AActor* HitActor = Hit.GetActor();
        if (HitActor && HitActor->FindComponentByClass<UDamageSystem>())
        {
            OutActors.AddUnique(HitActor);

            FDamageInfo damageInfo;

            damageInfo.Amount = 100.0f;
            damageInfo.DamageType = EDamageTransmitter::Projectile;
            damageInfo.DamageResponse = EDamageResponse::None;
            damageInfo.ShouldDamageInvincible = true;
            damageInfo.CanBeBlocked = true;
            damageInfo.CanBeParried = false;
            damageInfo.ShouldForceInterrupt = false;

            HitActor->FindComponentByClass<UDamageSystem>()->TakeDamage(damageInfo, GetOwner());

            // Print actor name to screen
            /*if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green,
                    FString::Printf(TEXT("Found actor with DamageSystem: %s"), *HitActor->GetName()));
            }*/
        }
    }

}