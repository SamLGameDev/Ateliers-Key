// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Damageable.h"
#include "BaseBodyPart.generated.h"

class UBaseArchetype;
class ABaseProcEnemy;
/**
 * 
 */
UCLASS()
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

	UFUNCTION(BlueprintCallable)
	virtual void AttatchPart(ABaseProcEnemy* Enemy) {};

	UFUNCTION(BlueprintCallable)
	virtual const int GetCost() const
	{
		return PartCost;
	}

protected:

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	virtual void RemoveFromAllOldArchetypes() {};

	virtual void AddToAllCurrentArchetypes() {};
	
	UPROPERTY(EditAnywhere)
	TArray<UBaseArchetype*> Archetypes;

	TArray<UBaseArchetype*> OldArchetypes;

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
