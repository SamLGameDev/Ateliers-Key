// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManager.h"
#include "Kismet/GameplayStatics.h"
#include "SettingsSave.h"
#include "SoundSubsystem.h"
#include "Sound/SoundClass.h"

void USoundManager::PlayRandomSound2D(const UObject* WorldContextObject, const ESoundUse Type, const FName SubType, const FName Map, const float StartTime)
{
	USoundSubsystem* subsystem =  WorldContextObject->GetWorld()->GetGameInstance()->GetSubsystem<USoundSubsystem>();

	subsystem->PlayRandomSound2D(Type, SubType, Map, StartTime);
}

void USoundManager::PlayRandomMusic(const UObject* WorldContextObject, const FName SubType, const FName Map, const float StartTime)
{
	USoundSubsystem* subsystem =  WorldContextObject->GetWorld()->GetGameInstance()->GetSubsystem<USoundSubsystem>();
	subsystem->PlayRandomMusic(SubType, Map, StartTime);
}

void USoundManager::PlayRandomSoundAtLocation(const UObject* WorldContextObject, const FVector Location, const ESoundUse Type, const FName SubType, const FName Map, const float StartTime)
{
	USoundSubsystem* subsystem =  WorldContextObject->GetWorld()->GetGameInstance()->GetSubsystem<USoundSubsystem>();
	subsystem->PlayRandomSoundAtLocation(Location, Type, SubType, Map, StartTime);
}

void USoundManager::StopMusic(UObject* WorldContextObject)
{
	USoundSubsystem* subsystem =  WorldContextObject->GetWorld()->GetGameInstance()->GetSubsystem<USoundSubsystem>();
	subsystem->StopMusic();
}

void USoundManager::PlayRandomMusicBlend(const UObject* WorldContextObject, const FName SubType, const FName Map,
	const float StartTime, const float BlendSpeed)
{
	USoundSubsystem* subsystem =  WorldContextObject->GetWorld()->GetGameInstance()->GetSubsystem<USoundSubsystem>();
	subsystem->PlayRandomMusicBlend(SubType, Map, StartTime, BlendSpeed);
}

float USoundManager::GetPlaybackTime(const UAudioComponent* Component)
{
	if (!Component->IsPlaying()) return 0.0f;
	return Component->TimeAudioComponentPlayed;
}

