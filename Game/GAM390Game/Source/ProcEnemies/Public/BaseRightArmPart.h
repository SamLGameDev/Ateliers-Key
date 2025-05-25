// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseArmPart.h"
#include "BaseRightArmPart.generated.h"

/**
 * 
 */
UCLASS()
class PROCENEMIES_API ABaseRightArmPart : public ABaseArmPart
{
	GENERATED_BODY()

public:
	virtual void AttatchPart(ABaseProcEnemy* Enemy) override;

protected:

	virtual void PostLoad() override;

};
