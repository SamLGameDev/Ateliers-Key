// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageTransmitter.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EDamageTransmitter : uint8
{
	None UMETA(DisplayName = "None"),
	Melee UMETA(DisplayName = "Melee"),
	Projectile UMETA(DisplayName = "Projectile"),
	Explosion UMETA(DisplayName = "Explosion"),
	Environment UMETA(DisplayName = "Environment")
	
};
