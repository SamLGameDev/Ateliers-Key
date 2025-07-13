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

	void Initialise(const float InDialation, const float InLifeTime, const float InitialStartDelay);

	void StartInitialDelay(const float InitialStartDelay, const float InLifeSpan);

	UFUNCTION()
	void SetUpDilation(const float InDialation);

	void StartLifeSpan(const float InLifeTime);

	const bool IsCurrentlyDelayed() const
	{
		return GetWorld()->GetTimerManager().IsTimerActive(DelayHandle);
	}


	/// <summary>
	/// starts the dilation, only if a delay isnt ongoing. returns -1 if it is, else the current dilation rate
	/// </summary>
	/// <param name="InLifeTime"></param>
	/// <returns></returns>
	UFUNCTION()
	void StartDilation(const float InLifeTime);

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

	FTimerHandle DelayHandle;


	float Dialation;

	float TimeOfCreation;

	float LifeTime;


};
