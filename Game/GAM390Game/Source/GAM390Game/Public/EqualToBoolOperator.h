// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Operator.h"
#include "EqualToBoolOperator.generated.h"

/**
 * 
 */
UCLASS()
class GAM390GAME_API UEqualToBoolOperator : public UOperator
{
	GENERATED_BODY()
public:
	/// <summary>
	/// Will return true if first value is equal to second value
	/// </summary>
	/// <param name="FirstValue"></param>
	/// <param name="SecondValue"></param>
	/// <returns></returns>
	const inline bool Compare(const bool FirstValue, const bool SecondValue) const override {
		return FirstValue == SecondValue;
	}
	
};
