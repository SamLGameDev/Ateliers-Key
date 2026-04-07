// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectPoolingSubsystem.generated.h"


class UPoolingConfig;

USTRUCT(BlueprintType)
struct FObjectPoolInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> PoolClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 InitialSize;
};

struct FObjectPool
{
public:
	FObjectPoolInfo Info;
	TArray<AActor*> Objects;
};

/**
 * 
 */
UCLASS()
class POOLINGSYSTEM_API UObjectPoolingSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	AActor* GetActorFromPool(TSubclassOf<AActor> Class);

	UFUNCTION(BlueprintCallable)
	void ReturnActorToPool(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	AActor* GetActorFromPoolAtTransform(TSubclassOf<AActor> Class, FTransform Transform);

protected:
	
	TMap<TSubclassOf<AActor>, FObjectPool> Pools;

	UPROPERTY()
	TObjectPtr<UPoolingConfig> PoolingConfig;
	
	
};
