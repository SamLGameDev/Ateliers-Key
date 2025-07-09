// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseVariableStore.h"
#include "uInt8Store.generated.h"

/**
 * 
 */
UCLASS()
class VARIABLESTORES_API UuInt8Store : public UPrimaryDataAsset, public BaseVariableStore<uint8>
{
	GENERATED_BODY()

public: 

	UFUNCTION(BlueprintCallable, Category = "VariableStores")
	virtual void SetObject(uint8 Object) override { BaseVariableStore<uint8>::SetObject(Object); };

	UFUNCTION(BlueprintCallable, Category = "VariableStores")
	virtual uint8 GetRegisteredObject() const override { return BaseVariableStore<uint8>::GetRegisteredObject(); };

	int operator++()
	{
		m_Object += 1;
		return m_Object;
	}

protected:
	uint8 m_Object = 0;


};
