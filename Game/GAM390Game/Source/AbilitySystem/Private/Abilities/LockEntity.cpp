// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LockEntity.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "BrainComponent.h"

void ULockEntity::CancelExecution()
{
}

void ULockEntity::StartExecution(AActor* Target)
{
	APawn* target = Cast<APawn>(Target);

	AController* controller = target->GetController();

	if (controller)
	{
		AAIController* aiController = Cast<AAIController>(controller);

		if (!aiController)
		{
			UE_LOG(LogTemp, Warning, TEXT("AiControrkpwrkenge"));
		}

		UBrainComponent* brain = aiController->GetBrainComponent();

		if (brain)
		{
			brain->StopLogic("EntityHasBeenLocked");
		}
	}

}