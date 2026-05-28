// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Operator.generated.h"

/**
 * A base class for Operators
 */
UCLASS(Abstract)
class UOperator : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	inline const virtual bool Compare(const float FirstValue, const float SecondValue) const { return false; };
	inline const virtual bool Compare(const bool FirstValue, const bool SecondValue) const { return false; };
};

