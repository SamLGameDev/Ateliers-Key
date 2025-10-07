// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "InputMappingContext.h"
#include "LockEntity.generated.h"

class AAIController;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ABILITYSYSTEM_API ULockEntity : public UAbility
{
	GENERATED_BODY()

public:

	void StartExecution() override {};

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void CancelExecution();

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void StartExecution(AActor* Target);


	UFUNCTION(BlueprintCallable, Category = "Ability")
	void StartPlayerLock(APawn* Player);

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	float Duration;

private:

	FTimerHandle EndLockHandle;

	AAIController* TargetController;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	UInputMappingContext* PlayerLockedMap;
	
};
