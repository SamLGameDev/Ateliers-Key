// Fill out your copyright notice in the Description page of Project Settings.


#include "Hardware/C_BaseHardwareAbility.h"

// Sets default values for this component's properties
UC_BaseHardwareAbility::UC_BaseHardwareAbility()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetComponentTickEnabled(false);

	// ...
}


// Called when the game starts
void UC_BaseHardwareAbility::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UC_BaseHardwareAbility::EnableAbility()
{
	SetComponentTickEnabled(true);
}


// Called every frame
void UC_BaseHardwareAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

