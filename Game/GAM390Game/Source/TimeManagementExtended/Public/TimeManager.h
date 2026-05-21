// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TimeManager.generated.h"

class UTimeDialationToken;

/**
 * 
 */
UCLASS()
class TIMEMANAGEMENTEXTENDED_API UTimeManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/// <summary>
	/// Set the time dialation, but if there is a current time dialation of lower dialation,
	/// it will be prioritised over the current dialation, and the current dialation will be added to a queue
	/// where it will be triggered if all lower dialations are cleared
	/// </summary>
	/// <param name="WorldContextObject"></param>
	/// <param name="InTime">The Dialiation</param>
	/// <param name="LifeTime">Optional param for a lifetime, will auto clear the dialation after this time has passed
	/// -1 means infinite time</param>
	/// <param name="InitialStartDelay"> Optional Param for a delay before the dialation begins, -1 for no delay </param>
	UFUNCTION(BlueprintCallable, Category = "TimeManagement")
	static UTimeDialationToken* SetTimeDialation(const UObject* WorldContextObject, const float InTime, const float LifeTime = -1, const float InitialStartDelay = -1);

	static void RemoveToken(UTimeDialationToken* Token);

	static const float SetTokenActive(UTimeDialationToken* Token);

	static const float GetCurrentDialation()
	{
		return CurrentTimeDialation;
	}

	/// <summary>
	/// Only to be used on start to ensure dilation is back to 1
	/// </summary>
	UFUNCTION(BlueprintCallable)
	static void ResetCurrentDialation()
	{
		CurrentTimeDialation = 1;
		CurrentDialations.Empty();
	}

private:

	static AWorldSettings* GetWorldSettings(const UObject* WorldContextObject);

	static float CurrentTimeDialation;

	static TArray<UTimeDialationToken*> CurrentDialations;
	
};
