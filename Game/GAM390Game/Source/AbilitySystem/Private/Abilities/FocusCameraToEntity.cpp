// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/FocusCameraToEntity.h"

void UFocusCameraToEntity::StartExecution(AActor* Target, const float Duration)
{
	AActor* owner = GetOwner();
	FVector from = owner->GetActorForwardVector();
	FVector dirToTarget = (Target->GetActorLocation() - owner->GetActorLocation()).GetSafeNormal();

	

	FTimerDelegate LookDel;
	LookDel.BindUFunction(this, "LookTowardsTarget", from, dirToTarget, 0, owner, Duration);

	LookHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(LookDel);



}

void UFocusCameraToEntity::LookTowardsTarget(const FVector From, const FVector To, const float Delta, APawn* Owner, const float Duration)
{
	if (Duration <= 0) return;

	FRotator newRot = FVector::SlerpNormals(From, To, Delta).ToOrientationRotator();

	Owner->GetController()->SetControlRotation(newRot);

	FTimerDelegate LookDel;
	LookDel.BindUFunction(this, "LookTowardsTarget", From, To, FMath::Clamp(Delta + (Speed * GetWorld()->GetDeltaSeconds()),0, 1), Owner, Duration - GetWorld()->GetDeltaSeconds());
	
	LookHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(LookDel);
}

void UFocusCameraToEntity::CancelExecution()
{
	GetWorld()->GetTimerManager().ClearTimer(LookHandle);
}