// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolingSubsystem.h"
#include "GI_Accessibility.h"
#include "PooledObject.h"
#include "PoolingConfig.h"

void UObjectPoolingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UGI_SanctumSettings* gi = Cast<UGI_SanctumSettings>(GetWorld()->GetGameInstance());

	if (!gi) return;
	
	PoolingConfig = Cast<UPoolingConfig>(gi->PoolingConfig);

	for (const auto& pool : PoolingConfig->Pools)
	{
		checkf(pool.PoolClass->ImplementsInterface(UPooledObject::StaticClass()),
			TEXT("Interface PooledObject not implemented on %s"),
			*pool.PoolClass->GetName());
		
		FObjectPool newPool;
		newPool.Info = pool;

		for (int32 i = 0; i < pool.InitialSize; i++)
		{
			AActor* actor = GetWorld()->SpawnActor(pool.PoolClass);
			newPool.Objects.Add(actor);
			IPooledObject::Execute_OnDisable(actor);
		}
		
		Pools.Add(pool.PoolClass, newPool);
	}
	
}

AActor* UObjectPoolingSubsystem::GetActorFromPool(TSubclassOf<AActor> Class)
{

	if (Pools[Class].Objects.IsEmpty())
	{
		Pools[Class].Objects.Add(GetWorld()->SpawnActor(Class));
		IPooledObject::Execute_OnDisable(Pools[Class].Objects.Last());
	}
	
	AActor* actor = Pools[Class].Objects.Pop(EAllowShrinking::No);
	return actor;	
}

void UObjectPoolingSubsystem::ReturnActorToPool(AActor* Actor)
{
	Pools[Actor->GetClass()].Objects.Push(Actor);
	IPooledObject::Execute_OnDisable(Actor);
}

AActor* UObjectPoolingSubsystem::GetActorFromPoolAtTransform(TSubclassOf<AActor> Class,
	FTransform Transform, AActor* Owner)
{
	AActor* actor = GetActorFromPool(Class);
	actor->SetActorTransform(Transform);
	IPooledObject::Execute_SetPoolObjectOwner(actor, Owner);
	IPooledObject::Execute_OnEnable(actor);
	return actor;
	
}
