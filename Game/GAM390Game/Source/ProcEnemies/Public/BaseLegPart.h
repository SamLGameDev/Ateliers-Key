// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBodyPart.h"
#include "BaseLegPart.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROCENEMIES_API ABaseLegPart : public ABaseBodyPart
{
	GENERATED_BODY()

public:

	virtual void AttatchPart(ABaseProcEnemy* Enemy) override;

protected:
	virtual void PostLoad() override;

	UPROPERTY(EditAnywhere)
	int	Speed;
};
