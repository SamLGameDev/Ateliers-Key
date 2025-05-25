// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseProcEnemyController.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS()
class PROCENEMIES_API ABaseProcEnemyController : public AAIController
{
	GENERATED_BODY()

public:

	virtual void SetUp(UBehaviorTree* Behavior);
	
};
