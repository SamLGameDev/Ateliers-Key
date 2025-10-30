// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LockEntity.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "BaseEnemyController.h"


void ULockEntity::CancelExecution()
{
	if (!TargetController)
	{
		return;
	}
	TargetController->RequestAiCanMove(StopId);
}

void ULockEntity::StartExecution(AActor* Target)
{
	APawn* target = Cast<APawn>(Target);

	if (AController* controller = target->GetController())
	{
		TargetController = Cast<ABaseEnemyController>(controller);

		if (!TargetController)
		{
			return;
		}

		StopId = TargetController->StopAIForDuration(Duration);
		
	}

}

void ULockEntity::StartPlayerLock(APawn* Player)
{
}
