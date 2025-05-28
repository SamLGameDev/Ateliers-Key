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
UCLASS()
class PROCENEMIES_API UBaseArchetype : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TSet<TSubclassOf<ABaseBodyPart>> GetHeadParts() const
	{
		return HeadParts;
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TSet<TSubclassOf<ABaseBodyPart>> GetTorsoParts() const
	{
		return TorsoParts;
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TSet<TSubclassOf<ABaseBodyPart>> GetLegParts() const
	{
		return LegParts;
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TSet<TSubclassOf<ABaseBodyPart>> GetLeftArmParts() const
	{
		return LeftArmParts;
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TSet<TSubclassOf<ABaseBodyPart>> GetRightArmParts() const
	{
		return RightArmParts;
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UBehaviorTree* GetBehaviorTree()
	{
		return Behavior;
	}

	UFUNCTION(BlueprintCallable)
	void RegisterHeadPart(TSubclassOf<ABaseBodyPart> Part);

	UFUNCTION(BlueprintCallable)
	void RegisterTorsoPart(TSubclassOf<ABaseBodyPart> Part);

	UFUNCTION(BlueprintCallable)
	void RegisterLegPart(TSubclassOf<ABaseBodyPart> Part);

	UFUNCTION(BlueprintCallable)
	void RegisterLeftArmPart(TSubclassOf<ABaseBodyPart> Part);

	UFUNCTION(BlueprintCallable)
	void RegisterRightArmPart(TSubclassOf<ABaseBodyPart> Part);

	UFUNCTION(BlueprintCallable)
	void RemoveFromHead(TSubclassOf<ABaseBodyPart> Part);
	UFUNCTION(BlueprintCallable)
	void RemoveFromTorso(TSubclassOf<ABaseBodyPart> Part);

	UFUNCTION(BlueprintCallable)
	void RemoveFromLeftArm(TSubclassOf<ABaseBodyPart> Part);

	UFUNCTION(BlueprintCallable)
	void RemoveFromRightArm(TSubclassOf<ABaseBodyPart> Part);

	UFUNCTION(BlueprintCallable)
	void RemoveFromLegs(TSubclassOf<ABaseBodyPart> Part);

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
	UPROPERTY(EditAnywhere)
	TSet<TSubclassOf<ABaseBodyPart>> HeadParts;

	UPROPERTY(VisibleAnywhere)
	TSet<TSubclassOf<ABaseBodyPart>> TorsoParts;

	UPROPERTY(VisibleAnywhere)
	TSet<TSubclassOf<ABaseBodyPart>> LegParts;

	UPROPERTY(VisibleAnywhere)
	TSet<TSubclassOf<ABaseBodyPart>> LeftArmParts;

	UPROPERTY(VisibleAnywhere)
	TSet<TSubclassOf<ABaseBodyPart>> RightArmParts;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* Behavior;

	
};
