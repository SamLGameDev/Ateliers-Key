// Fill out your copyright notice in the Description page of Project Settings.


#include "Hardware/C_HackingSlots.h"

void UC_HackingSlots::EnableAbility()
{
	UnlockedHackingSlots->SetObject(UnlockedHackingSlots->GetRegisteredObject()+ 1);
}

void UC_HackingSlots::BeginPlay()
{
	Super::BeginPlay();
	UnlockedHackingSlots->SetObject(0);
}
