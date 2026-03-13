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
	if (!TargetForLock) return;
	TargetForLock->GetComponentByClass<USkeletalMeshComponent>()->SetOverlayMaterial(nullptr);
}

void ULockEntity::StartExecution(AActor* Target)
{
	APawn* target = Cast<APawn>(Target);
	UE_LOG(LogTemp, Warning, TEXT("EndLockCall"));

	if (AController* controller = target->GetController())
	{
		TargetController = Cast<ABaseEnemyController>(controller);

		if (!TargetController)
		{
			return;
		}
		UE_LOG(LogTemp, Warning, TEXT("StartedLock"));
		TargetForLock = Target;
		TargetForLock->GetComponentByClass<USkeletalMeshComponent>()->SetOverlayMaterial(OverlayMat);
		StopId = TargetController->StopAIForDuration(Duration);
		FTimerDelegate CancelDel;

		CancelDel.BindUFunction(this, FName("CancelExecution"));
		FTimerHandle CancelHandle;
		GetWorld()->GetTimerManager().SetTimer(CancelHandle, CancelDel, Duration, false);
		
	}
	UE_LOG(LogTemp, Warning, TEXT("EndLockCall"));
}

void ULockEntity::StartPlayerLock(APawn* Player)
{
}
