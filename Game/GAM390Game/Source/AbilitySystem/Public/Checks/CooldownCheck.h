// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConditionCheck.h"
#include "CooldownCheck.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ABILITYSYSTEM_API UCooldownCheck : public UConditionCheck
{
	GENERATED_BODY()

	///True if not on cooldown
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool Check() const;

	///Starts or restarts the cooldown
	UFUNCTION(BlueprintCallable)
	void StartCooldown();
protected:

	UPROPERTY(EditDefaultsOnly)
	float CooldownDuration;
	
	FTimerHandle CooldownTimer;
	
	
};
