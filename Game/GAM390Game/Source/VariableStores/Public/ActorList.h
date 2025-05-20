// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseRunTimeSet.h"
#include "ActorList.generated.h"

/**
 * 
 */
UCLASS()
class VARIABLESTORES_API UActorList : public UPrimaryDataAsset, public BaseRunTimeSet<AActor*>
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "RunTimeSet|ActorList")
	virtual void RegisterObject(AActor* Object) override { BaseRunTimeSet<AActor*>::RegisterObject(Object); };

	UFUNCTION(BlueprintCallable, Category = "RunTimeSet|ActorList")
	virtual void DeregisterObject(AActor* Object) override { BaseRunTimeSet<AActor*>::DeregisterObject(Object); };
};
