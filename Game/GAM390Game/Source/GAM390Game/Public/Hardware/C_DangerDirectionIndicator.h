// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hardware/C_BaseHardwareAbility.h"
#include "C_DangerDirectionIndicator.generated.h"

enum class EDamageResponse : uint8;
class UGUI_DamageLocationIndicator;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAM390GAME_API UC_DangerDirectionIndicator : public UC_BaseHardwareAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	virtual void EnableAbility() override;

	UFUNCTION()
	virtual void StartDamageIndicator(EDamageResponse DamageResponse, AActor* Source);

	UFUNCTION()
	void CalculateDirection(AActor* Source);

	UFUNCTION()
	virtual void HideIndicator();

protected:
	
	UPROPERTY()
	FTimerHandle FadeHandle;

	UPROPERTY()
	FTimerHandle TickHandle;

	UPROPERTY(EditDefaultsOnly)
	float FadeTime;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGUI_DamageLocationIndicator> DIClass;
	UGUI_DamageLocationIndicator* DamageIndicator;
	
};
