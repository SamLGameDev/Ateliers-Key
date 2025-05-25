// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseArchetype.generated.h"

class ABaseBodyPart;
class UBehaviorTree;
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
	FORCEINLINE TArray<ABaseBodyPart*> GetLeftArmParts() const
	{
		return LeftArmParts;
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<ABaseBodyPart*> GetRightArmParts() const
	{
		return RightArmParts;
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UBehaviorTree* GetBehaviorTree()
	{
		return Behavior;
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
	FORCEINLINE void RegisterLeftArmPart(ABaseBodyPart* Part)
	{
		LeftArmParts.Add(Part);
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void RegisterRightArmPart(ABaseBodyPart* Part)
	{
		RightArmParts.Add(Part);
	}

	UFUNCTION(BlueprintCallable)
	virtual bool CheckCompleteBodyPossible()
	{
		return !(
			HeadParts.IsEmpty() ||
			TorsoParts.IsEmpty() ||
			LegParts.IsEmpty() ||
			LeftArmParts.IsEmpty() ||
			RightArmParts.IsEmpty()
			);
	}

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<ABaseBodyPart*> HeadParts;

	UPROPERTY(VisibleAnywhere)
	TArray<ABaseBodyPart*> TorsoParts;

	UPROPERTY(VisibleAnywhere)
	TArray<ABaseBodyPart*> LegParts;

	UPROPERTY(VisibleAnywhere)
	TArray<ABaseBodyPart*> LeftArmParts;

	UPROPERTY(VisibleAnywhere)
	TArray<ABaseBodyPart*> RightArmParts;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* Behavior;

	
};
