// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <DamageTransmitter.h>
#include "Damageable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DAMAGESYSTEM_API IDamageable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="UDamageable")
	void TakeDamage(double Amount, EDamageTransmitter DamageType, AActor* Dealer, EPhysicalSurface HitSurface);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UDamageable")
	void ReturnAttackToken(int32 Amount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="UDamageable")
	void ReserveAttackToken(int32 Amount, bool& Success);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="UDamageable")
	void IsDead(bool& Dead);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="UDamageable")
	void GetTeamNumber(int32& TeamNumber);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="UDamageable")
	void GetCurrentHealth(double& CurrentHealth);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="UDamageable")
	void GetMaxHealth(double& MaxHealth);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="UDamageable")
	void Heal(double Amount);
};
