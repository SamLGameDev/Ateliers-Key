// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sound/SoundCue.h"
#include "SoundTypes.h"
#include "Components/AudioComponent.h"
#include "SoundManager.generated.h"



/**
 * 
 */
UCLASS(NotPlaceable)
class SOUNDMANAGEMENT_API USoundManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	static void PlayRandomSound2D(const UObject* WorldContextObject, const ESoundUse Type = ESoundUse::Any, const FName SubType = "None", const FName Map = "None", const float StartTime = 0.0f);

	UFUNCTION(BlueprintCallable)
	static void PlayRandomMusic(const UObject* WorldContextObject, const FName SubType = "None", const FName Map = "None", const float StartTime = 0.0f);

	UFUNCTION(BlueprintCallable)
	static void PlayRandomSoundAtLocation(const UObject* WorldContextObject, const FVector Location, const ESoundUse Type = ESoundUse::Any, const FName SubType = "None", const FName Map = "None", const float StartTime = 0.0f);

	UFUNCTION(BlueprintCallable)
	static void StopMusic(UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable)
	static void PlayRandomMusicBlend(const UObject* WorldContextObject, const FName SubType = "None", const FName Map = "None", const float StartTime = 0.0f, const float BlendSpeed = 1);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetPlaybackTime(const UAudioComponent* Component);
};
