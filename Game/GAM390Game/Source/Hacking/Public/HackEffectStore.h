// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseRunTimeSet.h"
#include "HackEffectStore.generated.h"

class UHackEffect;

/**
 * 
 */
UCLASS()
class HACKING_API UHackEffectStore : public UPrimaryDataAsset, public BaseRunTimeSet<UHackEffect*>
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "RunTimeSet|HackList")
	virtual void RegisterObject(UHackEffect* Object) override { BaseRunTimeSet<UHackEffect*>::RegisterObject(Object); };

	UFUNCTION(BlueprintCallable, Category = "RunTimeSet|HackList")
	virtual void DeregisterObject(UHackEffect* Object) override
	{
		BaseRunTimeSet<UHackEffect*>::DeregisterObject(Object);
	};

	UFUNCTION(BlueprintCallable, Category = "RunTimeSet|HackList")
	virtual void Clear() override { BaseRunTimeSet<UHackEffect*>::Clear(); };
};
