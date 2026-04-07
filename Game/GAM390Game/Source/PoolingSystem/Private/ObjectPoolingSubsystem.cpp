// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolingSubsystem.h"
#include "GI_Accessibility.h"
#include "PoolingConfig.h"

void UObjectPoolingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UGI_SanctumSettings* gi = Cast<UGI_SanctumSettings>(GetWorld()->GetGameInstance());

	if (!gi) return;
	
	PoolingConfig = Cast<UPoolingConfig>(gi->PoolingConfig);

	for (const auto& pool : PoolingConfig->Pools)
	{
		FObjectPool newPool;
		newPool.Info = pool;

		for (int32 i = 0; i < pool.InitialSize; i++)
		{
			newPool.Objects.Add(GetWorld()->SpawnActor(pool.PoolClass));
			newPool.Objects.Last()->SetActorHiddenInGame(true);
		}
		
		Pools.Add(pool.PoolClass, newPool);
	}
	
}

AActor* UObjectPoolingSubsystem::GetActorFromPool(TSubclassOf<AActor> Class)
{

	if (Pools[Class].Objects.IsEmpty())
	{
		Pools[Class].Objects.Add(GetWorld()->SpawnActor(Class));
		Pools[Class].Objects.Last()->SetActorHiddenInGame(true);
	}
	
	AActor* actor = Pools[Class].Objects.Pop(EAllowShrinking::No);
	return actor;	
}

void UObjectPoolingSubsystem::ReturnActorToPool(AActor* Actor)
{
	Pools[Actor->GetClass()].Objects.Push(Actor);
	Actor->SetActorHiddenInGame(true);
}

AActor* UObjectPoolingSubsystem::GetActorFromPoolAtTransform(TSubclassOf<AActor> Class, FTransform Transform)
{
	AActor* actor = GetActorFromPool(Class);
	actor->SetActorTransform(Transform);
	actor->SetActorHiddenInGame(false);
	return actor;
	
}
