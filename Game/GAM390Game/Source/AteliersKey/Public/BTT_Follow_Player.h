// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Follow_Player.generated.h"

/**
 * 
 */
UCLASS()
class ATELIERSKEY_API UBTT_Follow_Player : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_Follow_Player();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Offset")
	float RightOffset = 150.0f;

	UPROPERTY(EditAnywhere, Category = "Offset")
	float ForwardOffset = 100.0f;
	
};
