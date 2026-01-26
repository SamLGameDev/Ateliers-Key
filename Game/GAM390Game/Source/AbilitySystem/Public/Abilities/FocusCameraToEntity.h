// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "FocusCameraToEntity.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ABILITYSYSTEM_API UFocusCameraToEntity : public UAbility
{
	GENERATED_BODY()
public:


	void StartExecution() override {};

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void CancelExecution();

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void StartExecution(AActor* Target, const float Duration);

	UFUNCTION()
	void LookTowardsTarget(const FVector From, const float Delta, APawn* Owner, const float Duration, const AActor* Target);

protected:

	UPROPERTY(EditDefaultsOnly)
	float Speed;

	FTimerHandle LookHandle;
};
