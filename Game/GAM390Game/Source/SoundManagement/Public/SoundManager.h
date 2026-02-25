// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sound/SoundCue.h"
#include "SoundTypes.h"
#include "Components/AudioComponent.h"
#include "SoundManager.generated.h"





USTRUCT(BlueprintType)
struct FSoundRow : public FTableRowBase
{
	GENERATED_BODY();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESoundUse Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundCue* Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PitchMultiplier = 1.0f;

	///The Map this sound is in, so if we have combat music for a specific map, you can add it here
	/// None is the same as Any
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Map = "None";

	/// I.e. Combat, Death, Enemy Death, etc...
	/// None is the same as Any
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SubType = "None";


	/// Fine to leave blank
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundConcurrency* Concurrency = nullptr;

	/// Only used in PlaySoundAtLocation, fine to leave empty. Dictates things like sound falloff
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundAttenuation* Attenuation = nullptr;

	/// Only used in PlaySoundAtLocation, fine to leave empty
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInitialActiveSoundParams* InitalParams = nullptr;

};


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
	static void StopMusic();

	static void GetRandomSound(TArray<FSoundRow*>& Rows, const ESoundUse Type, const FName& SubType, const FName& Map);

	UFUNCTION(BlueprintCallable)
	static void SetSoundTable(UDataTable* Table)
	{
		SoundDataTable = Table;
	};

	static void SyncVolume();
	
	UFUNCTION(BlueprintCallable)
	static void PlayRandomMusicBlend(const UObject* WorldContextObject, const FName SubType = "None", const FName Map = "None", const float StartTime = 0.0f);
	

private:

	static const bool IsMatchingType(const FSoundRow* row, const ESoundUse Type);

	static const bool IsMatchingSubType(const FSoundRow* row, const FName SubType);

	static const bool IsMatchingMap(const FSoundRow* row, const FName Map);

	static void FilterRows(TArray<FSoundRow*>& Rows, const ESoundUse Type, const FName& SubType, const FName& Map);
	
	static void BlendMusicDown();
	
	static void BlendMusicIn(const UObject* WorldContextObject, USoundCue* Sound, const float Volume, const float PitchMultiplier, const float StartTime, USoundConcurrency* Concurrency);

	static UDataTable* SoundDataTable;
	static TWeakObjectPtr<UAudioComponent> CurrentMusicComponent;
	
	static float BlendSpeed;
};
