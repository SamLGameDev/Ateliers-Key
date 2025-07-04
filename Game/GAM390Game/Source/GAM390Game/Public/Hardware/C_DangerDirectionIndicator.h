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
UCLASS()
class GAM390GAME_API UC_DangerDirectionIndicator : public UC_BaseHardwareAbility
{
	GENERATED_BODY()

public:

	virtual void EnableAbility() override;

	virtual void StartDamageIndicator(EDamageResponse Response, AActor* Source);

protected:
	 
	UPROPERTY(EditDefaultsOnly)
	UGUI_DamageLocationIndicator* DamageIndicator;
	
};
