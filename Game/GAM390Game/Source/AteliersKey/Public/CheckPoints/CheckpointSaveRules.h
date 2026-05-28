// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CheckpointSaveRules.generated.h"

/**
 * 
 */
UCLASS()
class ATELIERSKEY_API UCheckpointSaveRules : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "SaveSlots", BlueprintPure)
	static FString MakeSaveSlotName(const uint8& Slot)
	{
		return "Save" + FString::FromInt(Slot);
	}
	
	

	
};
