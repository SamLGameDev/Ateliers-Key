// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBodyPart.h"
#include "BaseArmPart.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROCENEMIES_API ABaseArmPart : public ABaseBodyPart
{
	GENERATED_BODY()

protected:
	virtual void PostLoad() override;

	UPROPERTY(EditAnywhere)
	int	Damage;
	
	
};
