// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LockEntity.h"
#include "AIController.h"
#include "BrainComponent.h"


void ULockEntity::CancelExecution()
{
	if (!TargetController)
	{
		return;
	}
	
	TargetController->GetBrainComponent()->StartLogic();
	GetWorld()->GetTimerManager().ClearTimer(EndLockHandle);
}

void ULockEntity::StartExecution(AActor* Target)
{
	APawn* target = Cast<APawn>(Target);

	if (AController* controller = target->GetController())
	{
		TargetController = Cast<AAIController>(controller);

		if (!TargetController)
		{
			return;
		}

		UBrainComponent* brain = TargetController->GetBrainComponent();
		
		TargetController->ClearFocus(EAIFocusPriority::Gameplay);
		brain->StopLogic("EntityHasBeenLocked");

		FTimerDelegate lockDel;

		lockDel.BindUFunction(this, "CancelExecution");

		GetWorld()->GetTimerManager().SetTimer(EndLockHandle, lockDel, Duration, false);
		
	}

}

void ULockEntity::StartPlayerLock(APawn* Player)
{
}
