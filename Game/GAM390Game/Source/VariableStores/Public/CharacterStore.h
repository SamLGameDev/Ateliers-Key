// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseVariableStore.h"
#include "GameFramework/Character.h"
#include "CharacterStore.generated.h"

/**
 * 
 */
UCLASS()
class VARIABLESTORES_API UCharacterStore : public UPrimaryDataAsset, public BaseVariableStore<ACharacter*>
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "VariableStores")
	virtual void SetObject(ACharacter* Object) override
	{
		BaseVariableStore<ACharacter*>::SetObject(Object);
	};

	UFUNCTION(BlueprintCallable, Category = "VariableStores")
	virtual ACharacter* GetRegisteredObject() const override
	{
		return BaseVariableStore<ACharacter*>::GetRegisteredObject();
	};
	
};
