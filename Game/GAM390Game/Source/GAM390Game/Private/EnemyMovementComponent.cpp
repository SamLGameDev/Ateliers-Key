// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMovementComponent.h"

#include "InteractiveGizmo.h"


UEnemyMovementComponent::UEnemyMovementComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxSpeed = 400.f;
	Acceleration = 1000.f;
	Deceleration = 2000.f;
	TurningBoost = 8.f;
	bPositionCorrected = false;
	
	ResetMoveState();
}

void UEnemyMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UEnemyMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	
	if (ShouldSkipUpdate(DeltaTime)) return;
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Make sure that everything is still valid, and that we are allowed to move.
	if (!PawnOwner || !UpdatedComponent)
	{
		return;
	}
	
	if (IsExceedingMaxSpeed(MaxSpeed) == true)
	{
		Velocity = Velocity.GetUnsafeNormal() * MaxSpeed;
	}
	
	bPositionCorrected = false;
	// Move actor
	FVector Delta = Velocity * DeltaTime;
	
	AActor* owner = GetOwner();
	GetController()->GetDesiredRotation();
	owner->SetActorRotation(Velocity.GetSafeNormal().Rotation());
	
	// Get (and then clear) the movement vector that we set in ACollidingPawn::Tick
	if (!Delta.IsNearlyZero())
	{
		const FVector OldLocation = UpdatedComponent->GetComponentLocation();
		const FQuat Rotation = UpdatedComponent->GetComponentQuat();
		
		FHitResult Hit;
		SafeMoveUpdatedComponent(Delta, Rotation, true, Hit);
 
		// If we bumped into something, try to slide along it
		if (Hit.IsValidBlockingHit())
		{
			HandleImpact(Hit, DeltaTime, Delta);
			SlideAlongSurface(Delta, 1.f - Hit.Time, Hit.Normal, Hit);
			
		}
		
		if (!bPositionCorrected)
		{
			const FVector NewLocation = UpdatedComponent->GetComponentLocation();
			Velocity = ((NewLocation - OldLocation) / DeltaTime);
		}
	}
	UpdateComponentVelocity();
}

bool UEnemyMovementComponent::ResolvePenetrationImpl(const FVector& Adjustment, const FHitResult& Hit,
	const FQuat& NewRotation)
{
	bPositionCorrected |= Super::ResolvePenetrationImpl(Adjustment, Hit, NewRotation);
	return bPositionCorrected;
}
