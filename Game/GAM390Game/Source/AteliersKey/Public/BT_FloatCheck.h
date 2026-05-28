// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BT_FloatCheck.generated.h"



struct FBlackboardKeySelector;
class UBlackBoardComponent;
class UOperator;

/**
 * Checks a float key agains an input value
 */
UCLASS()
class ATELIERSKEY_API UBT_FloatCheck : public UBTDecorator
{
	GENERATED_BODY()

	UBT_FloatCheck();

private:

	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	void InitializeFromAsset(UBehaviorTree& Asset) override;

	UPROPERTY(EditAnywhere, Category = "Conditions")
	FBlackboardKeySelector m_FloatKey;

	UPROPERTY(EditAnywhere, Category = "Conditions")
	float m_CheckValue;

	UPROPERTY(EditAnywhere, Category = "Conditions")
	UOperator* m_Operation;
	

	
	
};
