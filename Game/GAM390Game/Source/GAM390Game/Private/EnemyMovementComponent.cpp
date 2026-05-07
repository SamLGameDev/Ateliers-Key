// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMovementComponent.h"

#include "NetworkReplayStreaming.h"
#include "GameFramework/PhysicsVolume.h"
#include "ProfilingDebugging/CookStats.h"


UEnemyMovementComponent::UEnemyMovementComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxSpeed = 400.f;
	FallingMaxSpeed =700.f;
	Acceleration = 1000.f;
	Deceleration = 2000.f;
	TurningBoost = 8.f;
	bPositionCorrected = false;
	RotationSpeed = 10.f;
	bIgnoreYaw = false;
	bIgnorePitch = false;
	bIgnoreRoll = false;
	GravityScale = 5.f;
	ResetMoveState();
}

void UEnemyMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	Mesh = PawnOwner->GetComponentByClass<USkeletalMeshComponent>();
}

void UEnemyMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	
	if (ShouldSkipUpdate(DeltaTime))
	{
		return;
	}
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AController* Controller = GetController();
	// Make sure that everything is still valid, and that we are allowed to move.
	if (!PawnOwner || !UpdatedComponent || !Controller)
	{
		return;
	}
	HandlePendingLaunch();
	
	if (MovementMode == Falling)
	{
		Velocity = NewFallVelocity(Velocity, -GetGravityDirection() * GetGravityZ(), DeltaTime);
		if (IsExceedingMaxSpeed(FallingMaxSpeed) == true)
		{
			Velocity = Velocity.GetUnsafeNormal() * MaxSpeed;
		}
		FVector Delta = Velocity * DeltaTime;
		FHitResult Hit;
		SafeMoveUpdatedComponent(Delta, PawnOwner->GetActorRotation(), true, Hit);
		if (Hit.IsValidBlockingHit())
		{
			HandleImpact(Hit, DeltaTime, Delta);
			SlideAlongSurface(Delta, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
	else if (MovementMode == Walking)
	{
		if (IsExceedingMaxSpeed(MaxSpeed) == true)
		{
			Velocity = Velocity.GetUnsafeNormal() * MaxSpeed;
		}
		bPositionCorrected = false;
		// Move actor
	
		FVector Delta = Velocity * DeltaTime;

		FRotator newRotation = FMath::Lerp<FRotator>(PawnOwner->GetActorRotation(), Controller->GetDesiredRotation(), RotationSpeed * DeltaTime);
	
		newRotation.Yaw = bIgnoreYaw ? PawnOwner->GetActorRotation().Yaw : newRotation.Yaw;
		newRotation.Pitch = bIgnorePitch ? PawnOwner->GetActorRotation().Pitch : newRotation.Pitch;
		newRotation.Roll = bIgnoreRoll ? PawnOwner->GetActorRotation().Roll : newRotation.Roll;
	
		PawnOwner->SetActorRotation(newRotation);

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
	}
	UpdateComponentVelocity();
}

void UEnemyMovementComponent::Launch(const FVector& LaunchVel, bool bXYOverride, bool bZOverride)
{
	FVector FinalVel = LaunchVel;

	if (!bXYOverride)
	{
		FinalVel.X += Velocity.X;
		FinalVel.Y += Velocity.Y;
	}
	if (!bZOverride)
	{
		FinalVel.Z += Velocity.Z;
	}
	if (IsActive())
	{
		PendingLaunchVelocity = FinalVel;
	}
}
bool UEnemyMovementComponent::ResolvePenetrationImpl(const FVector& Adjustment, const FHitResult& Hit,
                                                     const FQuat& NewRotation)
{
	bPositionCorrected |= Super::ResolvePenetrationImpl(Adjustment, Hit, NewRotation);
	return bPositionCorrected;
}

bool UEnemyMovementComponent::HandlePendingLaunch()
{
	if (!PendingLaunchVelocity.IsZero())
	{
		Velocity = PendingLaunchVelocity;
		PendingLaunchVelocity = FVector::ZeroVector;
		MovementMode = Falling;
		return true;
	}
	return false;
}

FVector UEnemyMovementComponent::NewFallVelocity(const FVector& InitialVelocity, FVector Gravity,
	float DeltaTime)
{
	FVector Result = InitialVelocity;

	if (DeltaTime > 0.f)
	{
		// Apply gravity.
		Result += Gravity * DeltaTime;

		// Don't exceed terminal velocity.
		const float TerminalLimit = FMath::Abs(GetPhysicsVolume()->TerminalVelocity);
		if (Result.SizeSquared() > FMath::Square(TerminalLimit))
		{
			const FVector GravityDir = Gravity.GetSafeNormal();
			if ((Result | GravityDir) > TerminalLimit)
			{
				Result = FVector::PointPlaneProject(Result, FVector::ZeroVector, GravityDir) + GravityDir * TerminalLimit;
			}
		}
	}

	return Result;
}
