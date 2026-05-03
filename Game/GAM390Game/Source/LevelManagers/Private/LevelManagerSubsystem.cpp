// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"


ULevelLoadWaitToken* ULevelManagerSubsystem::WaitUntilLevelsAreVisible(const TArray<FName>& Levels)
{
	ULevelLoadWaitToken* token = NewObject<ULevelLoadWaitToken>();
	FTimerDelegate timerDelegate;
	timerDelegate.BindUFunction(this, "WaitForLevelsToBeLoaded", Levels,token);
	GetWorld()->GetTimerManager().SetTimerForNextTick(timerDelegate);
	CurrentWaitTokens.Add(token);
	return token;
}

void ULevelManagerSubsystem::WaitForLevelsToBeLoaded(const TArray<FName>& Levels, ULevelLoadWaitToken* Token)
{
	for (const auto& level : Levels)
	{
		ULevelStreaming* streamedLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), level);
		if (!streamedLevel) continue;
		if (!streamedLevel->IsLevelVisible())
		{
			ScheduleLevelLoadedCheck(Levels, Token);
			return;
		}
	}

	SignalLevelsLoaded(Token);
}

void ULevelManagerSubsystem::ScheduleLevelLoadedCheck(const TArray<FName>& Levels, ULevelLoadWaitToken* Token)
{
	FTimerHandle timerHandle;
	FTimerDelegate timerDelegate;
	timerDelegate.BindUFunction(this, "WaitForLevelsToBeLoaded", Levels, Token);
	GetWorld()->GetTimerManager().SetTimer(timerHandle, timerDelegate, LevelsLoadedCheckRate, false);
}

void ULevelManagerSubsystem::SignalLevelsLoaded(ULevelLoadWaitToken* Token)
{
	Token->OnComplete.Broadcast();
	CurrentWaitTokens.Remove(Token);
}

