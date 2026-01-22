// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LifeSteal.h"
#include "DamageSystem.h"


// Sets default values for this component's properties
ULifeSteal::ULifeSteal()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULifeSteal::BeginPlay()
{
	Super::BeginPlay();

	// ...

	DamageSystem = GetOwner()->GetComponentByClass<UDamageSystem>();
	
}


void ULifeSteal::CancelExecution()
{
	GetWorld()->GetTimerManager().ClearTimer(StealLoop);
}

void ULifeSteal::StartExecution(AActor* Target)
{
	if (!Target)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULifeSteal::StartExecution: Target is NULL!"));
		return;
	}
	
	UDamageSystem* TargetDS = Target->FindComponentByClass<UDamageSystem>();

	if (!TargetDS) return;
	
	FTimerDelegate LifeStealDel;

	LifeStealDel.BindUFunction(this, FName("LifeSteal"), TargetDS, Duration);

	StealLoop = GetWorld()->GetTimerManager().SetTimerForNextTick(LifeStealDel);
}

void ULifeSteal::HealReal()
{

	FTimerDelegate LifeStealDel;

	LifeStealDel.BindUFunction(this, FName("HealQuick"), Duration);

    GetWorld()->GetTimerManager().SetTimerForNextTick(LifeStealDel);
}

void ULifeSteal::HealQuick(float RemainingDuration)
{
	if (RemainingDuration <= 0) return;
	DamageSystem->Heal(HealPerTick * GetWorld()->GetDeltaSeconds());

	FTimerDelegate LifeStealDel;

	LifeStealDel.BindUFunction(this, FName("HealQuick"), RemainingDuration - GetWorld()->GetDeltaSeconds());

	GetWorld()->GetTimerManager().SetTimerForNextTick(LifeStealDel);
}

void ULifeSteal::LifeSteal(UDamageSystem* TargetDS, float RemainingDuration)
{
	if (RemainingDuration <= 0 || TargetDS->IsDead) return;

	FDamageInfo DamageInfo;
	DamageInfo.Amount = DamagePerTick * GetWorld()->GetDeltaSeconds();
	
	TargetDS->TakeDamage(DamageInfo, GetOwner());

	DamageSystem->HealTemp(HealPerTick * GetWorld()->GetDeltaSeconds());

	FTimerDelegate LifeStealDel;

	LifeStealDel.BindUFunction(this, FName("LifeSteal"), TargetDS, RemainingDuration - GetWorld()->GetDeltaSeconds());

	StealLoop = GetWorld()->GetTimerManager().SetTimerForNextTick(LifeStealDel);
}

// Called every frame
void ULifeSteal::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

