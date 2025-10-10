// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HackEffect.generated.h"

USTRUCT(BlueprintType)
struct FHackInfo
{
	GENERATED_BODY()

	UPROPERTY()
	UObject* Instigator;

	UPROPERTY()
	UObject* HackedObject;
};

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
	FText DisplayText = FText::GetEmpty();

	UFUNCTION(BlueprintCallable)
	virtual void ExecuteHack(const FHackInfo& HackInfo);

	UPROPERTY(EditAnywhere)
	FText Description;
};
