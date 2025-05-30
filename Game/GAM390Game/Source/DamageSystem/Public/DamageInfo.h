// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageResponse.h"
#include "DamageTransmitter.h"
#include "DamageInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DAMAGESYSTEM_API FDamageInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Info")
	float Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Info")
	EDamageTransmitter DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Info")
	EDamageResponse DamageResponse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Info")
	bool ShouldDamageInvincible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Info")
	bool CanBeBlocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Info")
	bool CanBeParried;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Info")
	bool ShouldForceInterrupt;

	FDamageInfo():Amount(0), ShouldDamageInvincible(false), CanBeBlocked(false), CanBeParried(false), ShouldForceInterrupt(false){}
	
};
