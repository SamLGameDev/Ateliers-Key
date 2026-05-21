// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/FocusCameraToEntity.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"

void UFocusCameraToEntity::StartExecution(AActor* Target, const float Duration)
{
	ACharacter* owner = Cast<ACharacter>(GetOwner());
	FVector from = owner->GetActorForwardVector();
	
	FTimerDelegate LookDel;
	LookDel.BindUFunction(this, "LookTowardsTarget", from, 0, owner, Duration, Target);

	LookHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(LookDel);



}

void UFocusCameraToEntity::LookTowardsTarget(const FVector From, const float Delta, APawn* Owner, const float Duration, const AActor* Target)
{
	if (Duration <= 0) return;
	if (!Target) return;
	UCameraComponent* cam = Owner->GetComponentByClass<UCameraComponent>();
	FVector dirToTarget = (Target->GetActorLocation() - cam->GetComponentLocation()).GetSafeNormal();
	FRotator newRot = FVector::SlerpNormals(From, dirToTarget, Delta).Rotation();

	Owner->GetController()->SetControlRotation(newRot);

	FTimerDelegate LookDel;
	LookDel.BindUFunction(this, "LookTowardsTarget", From, FMath::Clamp(Delta + (Speed * GetWorld()->GetDeltaSeconds()),0, 1), Owner, Duration - GetWorld()->GetDeltaSeconds(), Target);
	
	LookHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(LookDel);
}

void UFocusCameraToEntity::CancelExecution()
{
	GetWorld()->GetTimerManager().ClearTimer(LookHandle);
}