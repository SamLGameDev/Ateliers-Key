// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Operator.h"
#include "EqualToFloatOperator.generated.h"

/**
 * 
 */
UCLASS()
class GAM390GAME_API UEqualToFloatOperator : public UOperator
{
	GENERATED_BODY()
public:
	/// <summary>
	/// Will return true if first value is equal to second value
	/// </summary>
	/// <param name="FirstValue"></param>
	/// <param name="SecondValue"></param>
	/// <returns></returns>
	const inline bool Compare(const float FirstValue, const float SecondValue) const override {
		return FirstValue == SecondValue;
	}
	
};
