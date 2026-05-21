// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class AI_API ABaseEnemyController : public AAIController
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	uint8 StopAIForDuration(float Duration);

	UFUNCTION(BlueprintCallable)
	void RequestAiCanMove(uint8 ID);
	
	TArray<uint8> StopRequests;
	
};
