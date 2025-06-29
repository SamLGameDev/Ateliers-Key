// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManager.h"
#include "Kismet/GameplayStatics.h"

UDataTable* USoundManager::SoundDataTable;

TWeakObjectPtr<UAudioComponent> USoundManager::CurrentMusicComponent;

void USoundManager::PlayRandomSound2D(const UObject* WorldContextObject, const ESoundType Type, const FName SubType, const FName Map, const float StartTime)
{
	TArray<FSoundRow*> Rows;
	GetRandomSound(Rows, Type, SubType, Map);

	if (Rows.Num() == 0)
	{
		return;
	}

	int SoundIndex = FMath::RandRange(0, Rows.Num() - 1);

	UGameplayStatics::PlaySound2D
	(
		WorldContextObject,
		Rows[SoundIndex]->Sound,
		Rows[SoundIndex]->Volume,
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
	GetRandomSound(Rows, ESoundType::Music, SubType, Map);

	if (Rows.Num() == 0)
	{
		return;
	}

	int SoundIndex = FMath::RandRange(0, Rows.Num() -1);

	CurrentMusicComponent = TWeakObjectPtr<UAudioComponent>(UGameplayStatics::CreateSound2D
	(
		WorldContextObject,
		Rows[SoundIndex]->Sound,
		Rows[SoundIndex]->Volume,
		Rows[SoundIndex]->PitchMultiplier,
		StartTime,
		Rows[SoundIndex]->Concurrency,
		false,
		true
	));

	CurrentMusicComponent.Pin()->Play(StartTime);
}

void USoundManager::PlayRandomSoundAtLocation(const UObject* WorldContextObject, const FVector Location, const ESoundType Type, const FName SubType, const FName Map, const float StartTime)
{
	TArray<FSoundRow*> Rows;
	GetRandomSound(Rows, Type, SubType, Map);

	if (Rows.Num() == 0)
	{
		return;
	}

	int SoundIndex = FMath::RandRange(0, Rows.Num() -1 );

	UGameplayStatics::PlaySoundAtLocation
	(
		WorldContextObject,
		Rows[SoundIndex]->Sound,
		Location,
		Rows[SoundIndex]->Volume,
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

void USoundManager::GetRandomSound(TArray<FSoundRow*>& Rows, const ESoundType Type, const FName& SubType, const FName& Map)
{
	SoundDataTable->GetAllRows<FSoundRow>("", Rows);
	FilterRows(Rows, Type, SubType, Map);
}

void USoundManager::FilterRows(TArray<FSoundRow*>& Rows, const ESoundType Type, const FName& SubType, const FName& Map)
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

const bool USoundManager::IsMatchingType(const FSoundRow* row, const ESoundType Type)
{
	return row->Type == Type || row->Type == ESoundType::Any;
}

const bool USoundManager::IsMatchingSubType(const FSoundRow* row, const FName SubType)
{
	return SubType == "None" || SubType == row->SubType;
}

const bool USoundManager::IsMatchingMap(const FSoundRow* row, const FName Map)
{
	return Map == "None" || Map == row->Map;
}
