// Fill out your copyright notice in the Description page of Project Settings.


#include "GrenadeExplosion.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "DamageSystem.h"

// Sets default values
AGrenadeExplosion::AGrenadeExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGrenadeExplosion::BeginPlay()
{
	Super::BeginPlay();

    GetActorsInRadius(this, GetActorLocation(), 320, FoundActors);

	/*FVector Pos = GetActorLocation();
	float Radius = 320.0f;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	TArray<FHitResult> OutHits;
	bool bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(),
		Pos,
		Pos,
		Radius,
		ObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		OutHits,
		true
	);

	if (bHit) {
		for (const FHitResult& Hit : OutHits) {
			if (Hit.GetComponent()) {
				FString CompName = Hit.GetComponent()->GetName();
				GEngine->AddOnScreenDebugMessage(
					-1,
					5.0f,
					FColor::Green,
					FString::Printf(TEXT("Hit: %s"), *CompName)
				);
			}
		}
	}*/
}

// Called every frame
void AGrenadeExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrenadeExplosion::GetActorsInRadius(UObject* WorldContext, FVector Origin, float Radius, TArray<AActor*>& OutActors)
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

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan,
            FString::Printf(TEXT("Grenade found %d hits"), HitResults.Num()));
    }

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

            HitActor->FindComponentByClass<UDamageSystem>()->TakeDamage(damageInfo);

            // Print actor name to screen
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green,
                    FString::Printf(TEXT("Found actor with DamageSystem: %s"), *HitActor->GetName()));
            }
        }
    }

}

