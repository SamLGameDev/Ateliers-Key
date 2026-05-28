// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hardware/C_BaseHardwareAbility.h"
#include "uInt8Store.h"
#include "C_HackingSlots.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ATELIERSKEY_API UC_HackingSlots : public UC_BaseHardwareAbility
{
	GENERATED_BODY()

public:

	virtual void EnableAbility() override;

private:

	UFUNCTION()
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UuInt8Store* UnlockedHackingSlots;
	
};
