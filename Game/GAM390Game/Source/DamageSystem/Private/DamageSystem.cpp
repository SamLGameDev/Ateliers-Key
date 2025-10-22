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

void UDamageSystem::Heal(float Amount) {
	if (!IsDead) {
		CurrentHealth += Amount;

		CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
	}
}

void UDamageSystem::HealTemp(float Amount)
{
	if (!IsDead) {
		CurrentTempHealth += Amount;

		CurrentTempHealth = FMath::Clamp(CurrentTempHealth, 0.0f, MaxTempHealth);
	}
}

void UDamageSystem::TakeDamage(const FDamageInfo& DamageInfo, AActor* Source) {
	if (DamageInfo.CanBeBlocked && IsBlocking) {
		OnBlocked.Broadcast();
		return;
	}

	float DamageAmount =  DamageInfo.Amount;
	
	if (DamageInfo.HitSurface == SurfaceType1)
	{
		DamageAmount *= HeadshotDamageMultiplier;
	}
	

	if (!IsBlocking && !IsInvincible && !IsDead) {

		if (CurrentTempHealth > 0)
		{
			CurrentTempHealth -= DamageAmount;
			OnDamageResponse.Broadcast(DamageInfo.DamageResponse, Source);

			if (CurrentTempHealth <= 0.0f) {
				CurrentTempHealth = 0;
				return;
			}
			return;
		}

		CurrentHealth -= DamageAmount;

		if (CurrentHealth <= 0.0f) {
			IsDead = true;
			OnDeath.Broadcast();
		}
		else {
			OnDamageResponse.Broadcast(DamageInfo.DamageResponse, Source);
		}
	}
}

bool UDamageSystem::ReserveAttackToken(int32 Amount) {
	if (AttackTokensCount >= Amount) {
		AttackTokensCount -= Amount;

		return true;
	}
	else {
		return false;
	}
}

void UDamageSystem::ReturnAttackToken(int32 Amount) {
	AttackTokensCount += Amount;
}

void UDamageSystem::CallOnDeath(AActor* DamagedActor) {
	DamagedActor->Destroy();

	UE_LOG(LogTemp, Log, TEXT("Ded"));

	return;
}

void UDamageSystem::CallOnDamageResponse(const FDamageInfo& DamageResponse) {
	CurrentHealth -= DamageResponse.Amount;
}

