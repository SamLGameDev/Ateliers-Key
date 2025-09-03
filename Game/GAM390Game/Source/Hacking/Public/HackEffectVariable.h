// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseVariableStore.h"
#include "Hacks/HackEffect.h"
#include "HackEffectVariable.generated.h"

/**
 * 
 */
UCLASS()
class HACKING_API UHackEffectVariable : public UPrimaryDataAsset, public BaseVariableStore<UHackEffect*>
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "VariableStores")
	virtual void SetObject(UHackEffect* Object) override { BaseVariableStore<UHackEffect*>::SetObject(Object); };

	UFUNCTION(BlueprintCallable, Category = "VariableStores")
	virtual UHackEffect* GetRegisteredObject() const override
	{
		return BaseVariableStore<UHackEffect*>::GetRegisteredObject();
	};
};
