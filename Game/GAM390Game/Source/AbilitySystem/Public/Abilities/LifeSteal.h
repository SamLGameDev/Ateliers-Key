// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "LifeSteal.generated.h"

class UDamageSystem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ABILITYSYSTEM_API ULifeSteal : public UAbility
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULifeSteal();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void StartExecution() override {};

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void CancelExecution() override;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void StartExecution(AActor* Target);

	UFUNCTION()
	void LifeSteal(UDamageSystem* TargetDS, float RemainingDuration);
	
	UDamageSystem* DamageSystem;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	float Duration;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	float DamagePerTick;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	float HealPerTick;
	
	FTimerHandle StealLoop;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
