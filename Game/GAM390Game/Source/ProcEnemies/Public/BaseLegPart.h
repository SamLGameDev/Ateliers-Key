// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBodyPart.h"
#include "BaseLegPart.generated.h"

/**
 * 
 */
UCLASS()
class PROCENEMIES_API ABaseLegPart : public ABaseBodyPart
{
	GENERATED_BODY()

public:

	virtual void AttatchPart(ABaseProcEnemy* Enemy) override;

protected:

	virtual void RemoveFromAllOldArchetypes() override;

	virtual void AddToAllCurrentArchetypes() override;

	UPROPERTY(EditAnywhere)
	int	Speed;
};
