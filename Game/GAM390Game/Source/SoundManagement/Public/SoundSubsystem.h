// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SoundTypes.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "SoundSubsystem.generated.h"



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
UCLASS()
class SOUNDMANAGEMENT_API USoundSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UFUNCTION(BlueprintCallable)
	void PlayRandomSound2D(const ESoundUse Type = ESoundUse::Any, const FName SubType = "None", const FName Map = "None", const float StartTime = 0.0f);
    
	UFUNCTION(BlueprintCallable)
	void PlayRandomMusic(const FName SubType = "None", const FName Map = "None", const float StartTime = 0.0f);
    
	UFUNCTION(BlueprintCallable)
	void PlayRandomSoundAtLocation(const FVector Location, const ESoundUse Type = ESoundUse::Any, const FName SubType = "None", const FName Map = "None", const float StartTime = 0.0f);
    
	UFUNCTION(BlueprintCallable)
	void StopMusic();
    
	void GetRandomSound(TArray<FSoundRow*>& Rows, const ESoundUse Type, const FName& SubType, const FName& Map) const;
	
	void SyncVolume() const;
    	
	UFUNCTION(BlueprintCallable)
	void PlayRandomMusicBlend(const FName SubType = "None", const FName Map = "None", const float StartTime = 0.0f, float BlendSpeed = 0);
	
	UFUNCTION(BlueprintCallable)
	void PlaySoundBlend(const TArray<USoundCue*>& Sound, const float StartTime = 0.0f, float BlendSpeed = 0, USoundConcurrency* Concurrency=  nullptr, const float PitchMultiplier = 0);
	UFUNCTION(BlueprintCallable)
	void BlendOutSound(USoundCue* Sound, float BlendSpeed = 0);
    
    private:
		static bool IsMatchingType(const FSoundRow* row, const ESoundUse Type);

		static bool IsMatchingSubType(const FSoundRow* row, const FName SubType);

		static bool IsMatchingMap(const FSoundRow* row, const FName Map);

		static void FilterRows(TArray<FSoundRow*>& Rows, const ESoundUse Type, const FName& SubType, const FName& Map);
    	UFUNCTION()
    	void BlendMusicDown(float BlendSpeed) const;
    	UFUNCTION()
    	void BlendMusicIn(USoundCue* Sound, const float Volume, const float PitchMultiplier, const float StartTime, USoundConcurrency* Concurrency, float
	                      BlendSpeed);
		
		UFUNCTION()
	    void BlendMusicInMulti(const TArray<USoundCue*>& Sound, const float Volume, const float PitchMultiplier, const float StartTime, USoundConcurrency* Concurrency, float
					  BlendSpeed);
	
		UPROPERTY()
    	TObjectPtr<UDataTable> SoundDataTable;
		UPROPERTY()
    	TWeakObjectPtr<UAudioComponent> CurrentMusicComponent;
	
		UFUNCTION()
		void DereferenceSound(USoundCue* Sound);
		UPROPERTY()
		TArray<TWeakObjectPtr<UAudioComponent>> MusicComponents;
		
	
};
