// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeDialationToken.h"
#include "TimeManager.h"
#include "Kismet/GameplayStatics.h"

void UTimeDialationToken::Initialise(const float InDialation, const float InLifeTime)
{
	Dialation = InDialation;

	if(InLifeTime >= 0)
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UTimeDialationToken::LifetimeTick);
		LifeTime = InLifeTime;
		TimeOfCreation = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	}
}

void UTimeDialationToken::StopDialation()
{
	UTimeManager::RemoveToken(this);

	LifeTime = 0;
}

void UTimeDialationToken::LifetimeTick()
{
	const float TimeSinceCreation = UGameplayStatics::GetRealTimeSeconds(this) - TimeOfCreation;
#if WITH_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("%0.5f, %0.5f, %0.5f, %0.5f"), TimeSinceCreation, TimeOfCreation, UGameplayStatics::GetRealTimeSeconds(GetWorld()), UTimeManager::GetCurrentDialation())
#endif
	if (TimeSinceCreation >= LifeTime)
	{
		StopDialation();
		return;
	}
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UTimeDialationToken::LifetimeTick);

}

