// Fill out your copyright notice in the Description page of Project Settings.


#include "Hardware/C_DangerDirectionIndicator.h"
#include "DamageSystem.h"
#include "DamageResponse.h"
#include "Hardware/GUI_DamageLocationIndicator.h"

void UC_DangerDirectionIndicator::EnableAbility()
{
	GetOwner()->GetComponentByClass<UDamageSystem>()->OnDamageResponse.AddDynamic(this, &UC_DangerDirectionIndicator::StartDamageIndicator);
}

void UC_DangerDirectionIndicator::StartDamageIndicator(EDamageResponse Response, AActor* Source)
{
	const FVector dirToDealer = (GetOwner()->GetActorLocation() - Source->GetActorLocation()).GetSafeNormal();
	DamageIndicator->RotateToFace(dirToDealer);
}
