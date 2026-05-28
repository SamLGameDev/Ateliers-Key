// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTT_BoolCheck.generated.h"



struct FBlackboardKeySelector;
class UBlackBoardComponent;
class UOperator;

/**
 * Checks a float key agains an input value
 */
UCLASS()
class ATELIERSKEY_API UBTT_BoolCheck : public UBTDecorator
{
	GENERATED_BODY()

	UBTT_BoolCheck();

private:

	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	void InitializeFromAsset(UBehaviorTree& Asset) override;

	UPROPERTY(EditAnywhere, Category = "Conditions")
	FBlackboardKeySelector m_BoolKey;

	UPROPERTY(EditAnywhere, Category = "Conditions")
	bool m_CheckValue;

	UPROPERTY(EditAnywhere, Category = "Conditions")
	UOperator* m_Operation;
	

	
	
};
