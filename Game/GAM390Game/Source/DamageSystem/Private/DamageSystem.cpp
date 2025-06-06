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
	
	CurrentHealth = MaxHealth;
}


// Called every frame
void UDamageSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDamageSystem::Heal(float amount) {
	if (!IsDead) {
		CurrentHealth += amount;

		CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
	}
}

void UDamageSystem::TakeDamage(const FDamageInfo& DamageInfo) {
	if (DamageInfo.CanBeBlocked && IsBlocking) {
		OnBlocked.Broadcast();
		return;
	}

	if (!IsBlocking || !IsInvincible || !IsDead) {
		CurrentHealth -= DamageInfo.Amount;

		if (CurrentHealth <= 0.0f) {
			OnDeath.Broadcast();
		}
		else {
			OnDamageResponse.Broadcast(DamageInfo.DamageResponse);
		}
	}
}

void UDamageSystem::CallOnDeath(AActor* DamagedActor) {
	DamagedActor->Destroy();

	UE_LOG(LogTemp, Log, TEXT("Ded"));

	return;
}

void UDamageSystem::CallOnDamageResponse(const FDamageInfo& DamageResponse) {
	CurrentHealth -= DamageResponse.Amount;
}

