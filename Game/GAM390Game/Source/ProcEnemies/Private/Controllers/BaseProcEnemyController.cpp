// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BaseProcEnemyController.h"
#include "BehaviorTree/BehaviorTree.h"

void ABaseProcEnemyController::SetUp(UBehaviorTree* Behavior)
{
	RunBehaviorTree(Behavior);
}
