// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeDialationToken.h"
#include "TimeManager.h"
#include "Kismet/GameplayStatics.h"

void UTimeDialationToken::Initialise(const float InDialation, const float InLifeTime, const float InitialStartDelay)
{

	SetUpDilation(InDialation);

	if (InitialStartDelay > 0)
	{
		StartInitialDelay(InitialStartDelay, InLifeTime);
		return;
	}

	StartDilation(InLifeTime);


}

void UTimeDialationToken::StartInitialDelay(const float InitialStartDelay, const float InLifeSpan)
{
	FTimerDelegate DelayDel;
	DelayDel.BindUFunction(this, "StartDilation", InLifeSpan);
	GetWorld()->GetTimerManager().SetTimer(DelayHandle, DelayDel, InitialStartDelay, false, -1);
}

void UTimeDialationToken::SetUpDilation(const float InDialation)
{
	Dialation = InDialation;
}

void UTimeDialationToken::StartLifeSpan(const float InLifeTime)
{
	if (InLifeTime >= 0)
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UTimeDialationToken::LifetimeTick);
		LifeTime = InLifeTime;
		TimeOfCreation = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	}
}

void UTimeDialationToken::StartDilation(const float InLifeTime)
{
	
	if (GetWorld()->GetTimerManager().GetTimerRemaining(DelayHandle) > 0.0000001)
	{
		return;
	}
	StartLifeSpan(InLifeTime);
	UTimeManager::SetTokenActive(this);
	GetWorld()->GetTimerManager().ClearTimer(DelayHandle);

}

void UTimeDialationToken::StopDialation()
{
	UTimeManager::RemoveToken(this);

	LifeTime = 0;

	GetWorld()->GetTimerManager().ClearTimer(DelayHandle);
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

