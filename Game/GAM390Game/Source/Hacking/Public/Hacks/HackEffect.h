// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HackEffect.generated.h"

/**
 * 
 */
UCLASS()
class HACKING_API UHackEffect : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	float TimeToHack;

	UPROPERTY(EditAnywhere)
	FText DisplayText;

	UFUNCTION(BlueprintCallable)
	virtual void ExecuteHack(UObject* HackedObject) 
	{

	};
	
};
