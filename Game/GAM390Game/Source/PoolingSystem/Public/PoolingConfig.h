// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PoolingConfig.generated.h"

struct FObjectPoolInfo;
/**
 * 
 */
UCLASS()
class POOLINGSYSTEM_API UPoolingConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
	TArray<FObjectPoolInfo> Pools;
	
};
