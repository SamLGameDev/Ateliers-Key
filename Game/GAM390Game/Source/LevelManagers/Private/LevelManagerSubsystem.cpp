// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "WorldPartition/Cook/WorldPartitionCookPackage.h"


ULevelLoadWaitToken* ULevelManagerSubsystem::ReloadLevels(const TArray<TSoftObjectPtr<UWorld>>& Levels)
{
	ULevelLoadWaitToken* token = NewObject<ULevelLoadWaitToken>();
	FTimerDelegate timerDelegate;
	timerDelegate.BindUFunction(this, "UnloadLevels", Levels,token);
	GetWorld()->GetTimerManager().SetTimerForNextTick(timerDelegate);
	CurrentTokens.Add(token);
	return token;
}

void ULevelManagerSubsystem::UnloadLevels(const TArray<TSoftObjectPtr<UWorld>>& Levels, ULevelLoadWaitToken* Token)
{
	for (const auto& level : Levels)
	{
		if (level.IsNull()) continue;
		ULevelStreaming* streamingLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), FName(level.GetAssetName()));
		if (streamingLevel->IsLevelVisible() && !streamingLevel->IsStreamingStatePending())
		{
			UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(GetWorld(), level, {}, true);

			ScheduleLevelsUnloadedCheck(Levels, Token);
			return;
		}
	}

	LoadLevels(Levels, Token);
}

void ULevelManagerSubsystem::ScheduleLevelsUnloadedCheck(const TArray<TSoftObjectPtr<UWorld>>& Levels, ULevelLoadWaitToken* Token)
{
	FTimerHandle timerHandle;
	FTimerDelegate timerDelegate;
	timerDelegate.BindUFunction(this, "UnloadLevels", Levels, Token);
	GetWorld()->GetTimerManager().SetTimer(timerHandle, timerDelegate, LevelsUnloadedCheckRate, false);
}

void ULevelManagerSubsystem::LoadLevels(const TArray<TSoftObjectPtr<UWorld>>& Levels, ULevelLoadWaitToken* Token)
{
	for (const auto& level : Levels)
	{
		if (level.IsNull()) continue;
		ULevelStreaming* streamingLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), FName(level.GetAssetName()));
		if (!streamingLevel->IsLevelVisible() && !streamingLevel->IsStreamingStatePending())
		{
			UGameplayStatics::LoadStreamLevelBySoftObjectPtr(GetWorld(), level, true, true, {});
			ScheduleLevelsLoadedCheck(Levels, Token);
			return;
		}
	}

	SignalLevelsLoaded(Token);
}

void ULevelManagerSubsystem::ScheduleLevelsLoadedCheck(const TArray<TSoftObjectPtr<UWorld>>& Levels, ULevelLoadWaitToken* Token)
{
	FTimerHandle timerHandle;
	FTimerDelegate timerDelegate;
	timerDelegate.BindUFunction(this, "LoadLevels", Levels, Token);
	GetWorld()->GetTimerManager().SetTimer(timerHandle, timerDelegate, LevelsUnloadedCheckRate, false);
}

ULevelLoadWaitToken* ULevelManagerSubsystem::WaitUntilLevelsAreVisible(const TArray<FName>& Levels)
{
	ULevelLoadWaitToken* token = NewObject<ULevelLoadWaitToken>();
	FTimerDelegate timerDelegate;
	timerDelegate.BindUFunction(this, "WaitForLevelsToBeLoaded", Levels,token);
	GetWorld()->GetTimerManager().SetTimerForNextTick(timerDelegate);
	CurrentTokens.Add(token);
	return token;
}

void ULevelManagerSubsystem::WaitForLevelsToBeLoaded(const TArray<FName>& Levels, ULevelLoadWaitToken* Token)
{
	for (const auto& level : Levels)
	{
		ULevelStreaming* streamedLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), level);
		if (!streamedLevel)
		{
			continue;	
		}
		if (!streamedLevel->IsLevelVisible() || streamedLevel->IsStreamingStatePending())
		{
			ScheduleLevelLoadedCheck(Levels, Token);
			return;
		}
	}
	UGameplayStatics::FlushLevelStreaming(GetWorld());
	FTimerHandle timerHandle;
	FTimerDelegate timerDelegate;
	timerDelegate.BindUFunction(this, "SignalLevelsLoaded", Token);
	GetWorld()->GetTimerManager().SetTimer(timerHandle, timerDelegate, ExtraWaitTimeCheckRate, false);
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
	CurrentTokens.Remove(Token);
}

