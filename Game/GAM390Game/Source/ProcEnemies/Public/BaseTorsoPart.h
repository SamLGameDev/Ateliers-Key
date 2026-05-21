// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBodyPart.h"
#include "BaseTorsoPart.generated.h"

/**
 * 
 */
UCLASS()
class PROCENEMIES_API ABaseTorsoPart : public ABaseBodyPart
{
	GENERATED_BODY()

public:

	virtual void AttatchPart(ABaseProcEnemy* Enemy) override;

protected:

	virtual void RemoveFromAllOldArchetypes() override;

	virtual void AddToAllCurrentArchetypes() override;

	UPROPERTY(EditAnywhere)
	int	Armour;
	
};
