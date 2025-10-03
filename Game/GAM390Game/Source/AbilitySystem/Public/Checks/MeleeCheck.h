// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConditionCheck.h"
#include "MeleeCheck.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ABILITYSYSTEM_API UMeleeCheck : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMeleeCheck();
	bool DetectHitEntity(FHitResult& HitInfo) const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool Check(FHitResult& Result) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	float MeleeOffset;

	UPROPERTY(EditDefaultsOnly)
	FVector MeleeBoxHalfBounds;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
