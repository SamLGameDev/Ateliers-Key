// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseArchetype.generated.h"

class ABaseBodyPart;

/**
 * 
 */
UCLASS(Abstract)
class PROCENEMIES_API UBaseArchetype : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<ABaseBodyPart*> GetHeadParts() const
	{
		return HeadParts;
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<ABaseBodyPart*> GetTorsoParts() const
	{
		return TorsoParts;
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<ABaseBodyPart*> GetLegParts() const
	{
		return LegParts;
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<ABaseBodyPart*> GetArmParts() const
	{
		return ArmParts;
	}


	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RegisterHeadPart(ABaseBodyPart* Part)
	{
		HeadParts.Add(Part);
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RegisterTorsoPart(ABaseBodyPart* Part)
	{
		TorsoParts.Add(Part);
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RegisterLegPart(ABaseBodyPart* Part)
	{
		LegParts.Add(Part);
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RegisterArmPart(ABaseBodyPart* Part)
	{
		ArmParts.Add(Part);
	}

protected:
	UPROPERTY()
	TArray<ABaseBodyPart*> HeadParts;

	UPROPERTY()
	TArray<ABaseBodyPart*> TorsoParts;

	UPROPERTY()
	TArray<ABaseBodyPart*> LegParts;

	UPROPERTY()
	TArray<ABaseBodyPart*> ArmParts;

	
};
