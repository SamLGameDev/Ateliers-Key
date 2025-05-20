// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Damageable.h"
#include "BaseBodyPart.generated.h"

class UBaseArchetype;
/**
 * 
 */
UCLASS(Abstract)
class PROCENEMIES_API ABaseBodyPart : public AActor, public IDamageable
{
	GENERATED_BODY()

public:

	ABaseBodyPart();

	UFUNCTION(BlueprintCallable)
	virtual void ExecuteAbility();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetMaxDurability() const
	{
		return MaxDurability;
	}

	virtual void TakeDamage_Implementation(const int Damage) override;

protected:
	
	UPROPERTY(EditAnywhere)
	TArray<UBaseArchetype*> Archetypes;

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	int MaxDurability;

	UPROPERTY()
	int CurrentDurability;

	UPROPERTY(EditAnywhere)
	int PartCost;

	virtual void Destroy();

	
};
