// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageSystem.h"

// Sets default values for this component's properties
UDamageSystem::UDamageSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDamageSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UDamageSystem::Heal(float amount) {
	if (!IsDead) {
		Health += amount;

		Health = FMath::Clamp(Health, 0.0f, MaxHealth);
	}

	return Health;
}

void UDamageSystem::TakeDamage(FDamageInfo& DamageInfo) {
	if (DamageInfo.CanBeBlocked && IsBlocking) {
		return;
	}

	if (!IsBlocking || !IsInvincible || !IsDead) {
		Health -= DamageInfo.Amount;

		if (Health <= 0.0f) {
			OnDeath.Broadcast();
		}
	}
}

void UDamageSystem::CallOnDeath(AActor* DamagedActor) {
	DamagedActor->Destroy();
	return;
}

void UDamageSystem::CallOnDamageResponse(const FDamageInfo& DamageResponse) {
	Health -= DamageResponse.Amount;
}

