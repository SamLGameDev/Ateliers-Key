// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseVariableStore.h"
#include "BoolStore.generated.h"

/**
 * 
 */
UCLASS()
class VARIABLESTORES_API UBoolStore : public UPrimaryDataAsset, public BaseVariableStore<bool>
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "VariableStores")
	virtual bool GetRegisteredObject() const override { return BaseVariableStore<bool>::GetRegisteredObject(); };
	
};
