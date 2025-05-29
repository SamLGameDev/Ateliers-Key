// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	bool ShouldDamageInvincible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Info")
	bool CanBeBlocked;

	FDamageInfo():Amount(0), ShouldDamageInvincible(false), CanBeBlocked(false){}
	
};
