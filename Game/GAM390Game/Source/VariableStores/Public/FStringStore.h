// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseVariableStore.h"
#include "FStringStore.generated.h"

/**
 * 
 */
UCLASS()
class VARIABLESTORES_API UFStringStore : public UPrimaryDataAsset, public BaseVariableStore<FString>
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "VariableStores")
	virtual void SetObject(FString Object) override 
	{
		BaseVariableStore<FString>::SetObject(Object);
	};

	UFUNCTION(BlueprintCallable, Category = "VariableStores")
	virtual FString GetRegisteredObject() const override 
	{
		return BaseVariableStore<FString>::GetRegisteredObject();
	};


	
};
