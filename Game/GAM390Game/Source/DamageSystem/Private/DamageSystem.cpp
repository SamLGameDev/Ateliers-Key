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

	MaxAttackTokens = AttackTokensCount;
	
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
		
		OnHeal.Broadcast();
	}
}

void UDamageSystem::HealTemp(float Amount)
{
	if (!IsDead) {
		CurrentTempHealth += Amount;

		CurrentTempHealth = FMath::Clamp(CurrentTempHealth, 0.0f, MaxTempHealth);
		
		OnHealTemp.Broadcast();
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
				if (CurrentHealth < CriticalHealthThreashold)
				{
					OnCriticalThreasholdReached.Broadcast(DamageInfo.DamageResponse, Source);
				}
				
				return;
			}
			return;
		}

		const float HealthBeforeDamage = CurrentHealth;

		CurrentHealth -= DamageAmount;

		if (CurrentHealth < CriticalHealthThreashold && HealthBeforeDamage >= CriticalHealthThreashold)
		{
			OnCriticalThreasholdReached.Broadcast(DamageInfo.DamageResponse, Source);
		}

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

void UDamageSystem::ResetHealth()
{
	CurrentHealth = MaxHealth;
}

void UDamageSystem::CompleteReset()
{
	ResetHealth();
	CurrentTempHealth = 0;
	IsDead = 0;

	AttackTokensCount = MaxAttackTokens;
}

void UDamageSystem::StartHealthPerTick(const float& Amount, const float& Duration, uint8& ID, const bool& TempHealth)
{
	while (HealthPerTickHandles.Contains(ID))
	{
		ID = FMath::RandRange(0, 255);
	}

	FHealFunc HealFunc;
	if (TempHealth) HealFunc.BindDynamic(this, &UDamageSystem::HealTemp);
	else  HealFunc.BindDynamic(this, &UDamageSystem::Heal);
	
	FTimerDelegate HealTickDel;

	HealTickDel.BindUFunction(this, FName("HealTick"), Duration, Amount, ID, HealFunc);
	
	HealthPerTickHandles.Add(ID, GetWorld()->GetTimerManager().SetTimerForNextTick(HealTickDel));
}
void UDamageSystem::HealTick(const float Duration, const float Amount, const uint8 ID, const FHealFunc& HealFunc)
{
	if (Duration <= 0)
	{
		HealthPerTickHandles.Remove(ID);
		return;
	};
	HealFunc.Execute(Amount * GetWorld()->GetDeltaSeconds());

	FTimerDelegate HealTickDel;

	HealTickDel.BindUFunction(this, FName("HealTick"), Duration - GetWorld()->GetDeltaSeconds(), Amount, ID, HealFunc);

	HealthPerTickHandles[ID] = GetWorld()->GetTimerManager().SetTimerForNextTick(HealTickDel);
}

void UDamageSystem::CancelHealTick(const uint8& ID)
{
	GetWorld()->GetTimerManager().ClearTimer(HealthPerTickHandles[ID]);
	HealthPerTickHandles.Remove(ID);
}

void UDamageSystem::CallOnDeath(AActor* DamagedActor) {
	DamagedActor->Destroy();

	UE_LOG(LogTemp, Log, TEXT("Ded"));

	return;
}

void UDamageSystem::CallOnDamageResponse(const FDamageInfo& DamageResponse) {
	CurrentHealth -= DamageResponse.Amount;
}

