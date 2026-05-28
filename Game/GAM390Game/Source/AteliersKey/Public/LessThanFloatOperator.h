// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Operator.h"
#include "LessThanFloatOperator.generated.h"

/**
 * 
 */
UCLASS()
class ATELIERSKEY_API ULessThanFloatOperator : public UOperator
{
	GENERATED_BODY()
	
public:
	/// <summary>
	/// Returns true if FirstValue is less than SecondValue
	/// </summary>
	/// <param name="FirstValue"></param>
	/// <param name="SecondValue"></param>
	/// <returns></returns>
	const inline bool Compare(const float FirstValue, const float SecondValue) const override {
		return FirstValue < SecondValue;
	}
};
