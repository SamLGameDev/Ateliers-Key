// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseVariableStore.h"
#include "ActorStore.generated.h"

/**
 * 
 */
UCLASS()
class VARIABLESTORES_API UActorStore : public UPrimaryDataAsset, public BaseVariableStore<AActor*>
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "VariableStores")
	virtual void SetObject(AActor* Object) override { BaseVariableStore<AActor*>::SetObject(Object); };

	UFUNCTION(BlueprintCallable, Category = "VariableStores")
	virtual AActor* GetRegisteredObject() const override { return BaseVariableStore<AActor*>::GetRegisteredObject(); };
	
};
