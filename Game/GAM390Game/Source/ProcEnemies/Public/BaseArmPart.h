// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBodyPart.h"
#include "BaseArmPart.generated.h"

/**
 * 
 */
UCLASS()
class PROCENEMIES_API ABaseArmPart : public ABaseBodyPart
{
	GENERATED_BODY()

public:


protected:

	UPROPERTY(EditAnywhere)
	int	Damage;
	
	
};
