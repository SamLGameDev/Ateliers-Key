// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManager.h"
#include "Kismet/GameplayStatics.h"
#include "SettingsSave.h"
#include "Sound/SoundClass.h"

UDataTable* USoundManager::SoundDataTable;
float USoundManager::BlendSpeed = 1;

TWeakObjectPtr<UAudioComponent> USoundManager::CurrentMusicComponent;

void USoundManager::PlayRandomSound2D(const UObject* WorldContextObject, const ESoundUse Type, const FName SubType, const FName Map, const float StartTime)
{
	TArray<FSoundRow*> Rows;
	GetRandomSound(Rows, Type, SubType, Map);

	if (Rows.Num() == 0)
	{
		return;
	}

	int SoundIndex = FMath::RandRange(0, Rows.Num() - 1);

	USettingsSave* Save = Cast<USettingsSave>(UGameplayStatics::LoadGameFromSlot("settings", 0));
	
	UGameplayStatics::PlaySound2D
	(
		WorldContextObject,
		Rows[SoundIndex]->Sound,
		Save->MasterVolume,
		Rows[SoundIndex]->PitchMultiplier,
		StartTime,
		Rows[SoundIndex]->Concurrency,
		nullptr,
		false
	);


}

void USoundManager::PlayRandomMusic(const UObject* WorldContextObject, const FName SubType, const FName Map, const float StartTime)
{
	StopMusic();

	TArray<FSoundRow*> Rows;
	GetRandomSound(Rows, ESoundUse::Music, SubType, Map);

	if (Rows.Num() == 0)
	{
		return;
	}

	int SoundIndex = FMath::RandRange(0, Rows.Num() -1);

	USettingsSave* Save = Cast<USettingsSave>(UGameplayStatics::LoadGameFromSlot("settings", 0));

	CurrentMusicComponent = TWeakObjectPtr<UAudioComponent>(UGameplayStatics::CreateSound2D
	(
		WorldContextObject,
		Rows[SoundIndex]->Sound,
		Save->MusicVolume,
		Rows[SoundIndex]->PitchMultiplier,
		StartTime,
		Rows[SoundIndex]->Concurrency,
		false,
		true
	));

	CurrentMusicComponent.Pin()->Play(StartTime);
}

void USoundManager::PlayRandomSoundAtLocation(const UObject* WorldContextObject, const FVector Location, const ESoundUse Type, const FName SubType, const FName Map, const float StartTime)
{
	TArray<FSoundRow*> Rows;
	GetRandomSound(Rows, Type, SubType, Map);

	if (Rows.Num() == 0)
	{
		return;
	}

	int SoundIndex = FMath::RandRange(0, Rows.Num() -1 );

	USettingsSave* Save = Cast<USettingsSave>(UGameplayStatics::LoadGameFromSlot("settings", 0));

	UGameplayStatics::PlaySoundAtLocation
	(
		WorldContextObject,
		Rows[SoundIndex]->Sound,
		Location,
		Save->MasterVolume,
		Rows[SoundIndex]->PitchMultiplier,
		StartTime,
		Rows[SoundIndex]->Attenuation,
		Rows[SoundIndex]->Concurrency,
		Rows[SoundIndex]->InitalParams
	);
}

void USoundManager::StopMusic()
{
	if (CurrentMusicComponent.IsValid())
	{
		CurrentMusicComponent.Pin()->Stop();
		CurrentMusicComponent = nullptr;
	}
}

void USoundManager::GetRandomSound(TArray<FSoundRow*>& Rows, const ESoundUse Type, const FName& SubType, const FName& Map)
{
	SoundDataTable->GetAllRows<FSoundRow>("", Rows);
	FilterRows(Rows, Type, SubType, Map);
}

void USoundManager::FilterRows(TArray<FSoundRow*>& Rows, const ESoundUse Type, const FName& SubType, const FName& Map)
{
	TArray<FSoundRow*> FilteredRows;
	for (FSoundRow* row : Rows)
	{
		if (IsMatchingType(row, Type) && IsMatchingSubType(row, SubType) && IsMatchingMap(row, Map))
		{
			FilteredRows.Add(row);
		}
	}
	Rows = FilteredRows;
}

void USoundManager::BlendMusicDown()
{
	if (CurrentMusicComponent.IsValid())
	{
		CurrentMusicComponent->FadeOut(BlendSpeed, 0);
	}
	
	
}

void USoundManager::BlendMusicIn(const UObject* WorldContextObject, USoundCue* Sound, const float Volume,
	const float PitchMultiplier, const float StartTime, USoundConcurrency* Concurrency)
{
	CurrentMusicComponent = TWeakObjectPtr<UAudioComponent>(UGameplayStatics::CreateSound2D
	(
		WorldContextObject,
		Sound,
		Volume,
		PitchMultiplier,
		StartTime,
		Concurrency,
	false,
	true
	));
	CurrentMusicComponent.Pin()->FadeIn(BlendSpeed, Volume);
}

void USoundManager::SyncVolume()
{
	if (CurrentMusicComponent.IsValid())
	{
		USettingsSave* Save = Cast<USettingsSave>(UGameplayStatics::LoadGameFromSlot("settings", 0));
		CurrentMusicComponent.Pin()->SetVolumeMultiplier(Save->MusicVolume);
	}
}

void USoundManager::PlayRandomMusicBlend(const UObject* WorldContextObject, const FName SubType, const FName Map,
	const float StartTime)
{
	BlendMusicDown();
	
	
	StopMusic();

	TArray<FSoundRow*> Rows;
	GetRandomSound(Rows, ESoundUse::Music, SubType, Map);

	if (Rows.Num() == 0)
	{
		return;
	}

	int SoundIndex = FMath::RandRange(0, Rows.Num() -1);

	USettingsSave* Save = Cast<USettingsSave>(UGameplayStatics::LoadGameFromSlot("settings", 0));
	
	FTimerDelegate Delegate;
	Delegate.BindStatic(&USoundManager::BlendMusicIn, WorldContextObject, Rows[SoundIndex]->Sound, 
		Save->MusicVolume, Rows[SoundIndex]->PitchMultiplier, StartTime, Rows[SoundIndex]->Concurrency);
	FTimerHandle DelegateHandle;
	
	WorldContextObject->GetWorld()->GetTimerManager().SetTimer(DelegateHandle, Delegate, BlendSpeed, false);
}

const bool USoundManager::IsMatchingType(const FSoundRow* row, const ESoundUse Type)
{
	return row->Type == Type || row->Type == ESoundUse::Any;
}

const bool USoundManager::IsMatchingSubType(const FSoundRow* row, const FName SubType)
{
	return SubType == "None" || SubType == row->SubType;
}

const bool USoundManager::IsMatchingMap(const FSoundRow* row, const FName Map)
{
	return Map == "None" || Map == row->Map;
}
