// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TimeDialationToken.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TIMEMANAGEMENTEXTENDED_API UTimeDialationToken : public UObject
{
	GENERATED_BODY()
	
public:

	void Initialise(const float InDialation, const float InLifeTime);

	UFUNCTION(BlueprintCallable)
	void StopDialation();

	UFUNCTION(BlueprintCallable)
	const float GetDialation() const
	{
		return Dialation;
	}

	const bool operator<(const UTimeDialationToken& OtherToken) const
	{
		return Dialation < OtherToken.Dialation;
	}

	UFUNCTION()
	void LifetimeTick();



private:

	float Dialation;

	float TimeOfCreation;

	float LifeTime;


};
