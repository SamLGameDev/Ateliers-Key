// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GrenadeExplosion.h"
#include "Frag_GrenadeExplosion.generated.h"

/**
 * 
 */
UCLASS()
class DAMAGESYSTEM_API AFrag_GrenadeExplosion : public AGrenadeExplosion
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	void GetActorsInRadius(UObject* World, FVector Origin, float Radius, TArray<AActor*>& OutActors);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Array")
	TArray<AActor*> FoundActors;
	
};
