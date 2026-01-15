// Fill out your copyright notice in the Description page of Project Settings.


#include "Checks/CooldownCheck.h"

bool UCooldownCheck::Check() const
{
	return !GetWorld()->GetTimerManager().IsTimerActive(CooldownTimer);
}

void UCooldownCheck::StartCooldown()
{
	GetWorld()->GetTimerManager().ClearTimer(CooldownTimer);

	GetWorld()->GetTimerManager().SetTimer(CooldownTimer, CooldownDuration, false, -1);

}

float UCooldownCheck::GetCooldownRemainingPercent() const
{
	return GetWorld()->GetTimerManager().GetTimerRemaining(CooldownTimer) / CooldownDuration;
}
