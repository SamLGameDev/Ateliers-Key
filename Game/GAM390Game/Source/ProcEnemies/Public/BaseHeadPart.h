// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBodyPart.h"
#include "BaseHeadPart.generated.h"

/**
 * 
 */
UCLASS()
class PROCENEMIES_API ABaseHeadPart : public ABaseBodyPart
{
	GENERATED_BODY()

public:

	virtual void AttatchPart(ABaseProcEnemy* Enemy) override;

protected:
	virtual void RemoveFromAllOldArchetypes() override;

	virtual void AddToAllCurrentArchetypes() override;


	
};
