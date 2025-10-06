// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "LockEntity.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ABILITYSYSTEM_API ULockEntity : public UAbility
{
	GENERATED_BODY()

public:

	void StartExecution() override {};

	void CancelExecution() override;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void StartExecution(AActor* Target);

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	float Duration;
	
};
