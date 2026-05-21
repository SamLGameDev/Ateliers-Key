// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyController.h"
#include "BrainComponent.h"

uint8 ABaseEnemyController::StopAIForDuration(float Duration)
{
	if (StopRequests.IsEmpty())
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		GetBrainComponent()->StopLogic("EntityHasBeenLocked");
	}
	
	uint8 id = 0;
	while (StopRequests.Contains(id))
	{
		id = FMath::RandRange(0, 256);
	}
	StopRequests.Add(id);
	FTimerHandle Handle;
	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, FName("RequestAiCanMove"), id);
	
	GetWorld()->GetTimerManager().SetTimer(Handle, Delegate, Duration, false, -1);

	UE_LOG(LogTemp, Warning, TEXT("LockedAI"));
	
	return id;
}

void ABaseEnemyController::RequestAiCanMove(uint8 ID)
{
	StopRequests.Remove(ID);
	if (StopRequests.IsEmpty())
	{
		if (!GetBrainComponent()) return;
		
		GetBrainComponent()->StartLogic();
	}
}
