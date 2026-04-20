// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "EnemyMovementComponent.generated.h"

/**
 * 
 */
UCLASS(meta= (BlueprintSpawnableComponent))
class GAM390GAME_API UEnemyMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	UEnemyMovementComponent(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

private:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	//Begin UMovementComponent Interface
	virtual float GetMaxSpeed() const override { return MaxSpeed; }
public:
	
	/** Maximum velocity magnitude allowed for the controlled Pawn. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=EnemyMovement)
	float MaxSpeed;

	/** Acceleration applied by input (rate of change of velocity) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=EnemyMovement)
	float Acceleration;

	/** Deceleration applied when there is no input (rate of change of velocity) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=EnemyMovement)
	float Deceleration;

	/**
	 * Setting affecting extra force applied when changing direction, making turns have less drift and become more responsive.
	 * Velocity magnitude is not allowed to increase, that only happens due to normal acceleration. It may decrease with large direction changes.
	 * Larger values apply extra force to reach the target direction more quickly, while a zero value disables any extra turn force.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=EnemyMovement, meta=(ClampMin="0", UIMin="0"))
	float TurningBoost;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=EnemyMovement)
	float RotationSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=EnemyMovement)
	bool bIgnoreRoll;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=EnemyMovement)
	bool bIgnoreYaw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=EnemyMovement)
	bool bIgnorePitch;
	
protected:
	UPROPERTY(Transient)
	uint32 bPositionCorrected:1;

	virtual bool
	ResolvePenetrationImpl(const FVector& Adjustment, const FHitResult& Hit, const FQuat& NewRotation) override;
	
	TObjectPtr<USkeletalMeshComponent> Mesh;
	
};
