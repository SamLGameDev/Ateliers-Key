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
	TargetMesh->SetOverlayMaterial(nullptr);
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
		TargetForLock = Target;
		TArray<USkeletalMeshComponent*> SkeletalMeshComponents;
		Target->GetComponents<USkeletalMeshComponent>(SkeletalMeshComponents);
		TargetMesh = nullptr;
		for (auto& SkeletalMeshComponent : SkeletalMeshComponents)
		{
			if (SkeletalMeshComponent->ComponentHasTag("Body"))
			{
				TargetMesh = SkeletalMeshComponent;
				break;
			}
		}
	
		checkf(TargetMesh, TEXT("Found no mesh for lockEntity with tag Body"));
	
		TargetMesh->SetOverlayMaterial(OverlayMat);
		StopId = TargetController->StopAIForDuration(Duration);
		FTimerDelegate CancelDel;

		CancelDel.BindUFunction(this, FName("CancelExecution"));
		FTimerHandle CancelHandle;
		GetWorld()->GetTimerManager().SetTimer(CancelHandle, CancelDel, Duration, false);
		
	}
}

void ULockEntity::StartPlayerLock(APawn* Player)
{
}
