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
class ATELIERSKEY_API UC_DangerDirectionIndicator : public UC_BaseHardwareAbility
{
	GENERATED_BODY()

public:
	virtual void EnableAbility() override;

	UFUNCTION()
	virtual void StartDamageIndicator(EDamageResponse DamageResponse, AActor* Source);



protected:

	virtual UGUI_DamageLocationIndicator* GetIndicator();


	UPROPERTY(EditDefaultsOnly)
	uint8 NumberOfIndicators;

	UPROPERTY(EditDefaultsOnly)
	float FadeTime;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGUI_DamageLocationIndicator> DIClass;

	TArray<UGUI_DamageLocationIndicator*> UnusedIndicators;
	TArray<UGUI_DamageLocationIndicator*> ActiveIndicators;
	
};
