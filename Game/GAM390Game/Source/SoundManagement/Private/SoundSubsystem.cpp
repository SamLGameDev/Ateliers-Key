// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundSubsystem.h"
#include "GI_Accessibility.h"
#include "SettingsSave.h"
#include "Sound/SoundClass.h"


void USoundSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UGI_SanctumSettings* gi = Cast<UGI_SanctumSettings>(GetGameInstance());

	if (!gi) return;

	SoundDataTable = gi->SoundsTable;
}

void USoundSubsystem::PlayRandomSound2D(const ESoundUse Type, const FName SubType, const FName Map,
	const float StartTime)
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
		GetWorld(),
		Rows[SoundIndex]->Sound,
		Save->MasterVolume,
		Rows[SoundIndex]->PitchMultiplier,
		StartTime,
		Rows[SoundIndex]->Concurrency,
		nullptr,
		false
	);
}

void USoundSubsystem::PlayRandomMusic(const FName SubType, const FName Map, const float StartTime)
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
		GetWorld(),
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

void USoundSubsystem::PlayRandomSoundAtLocation(const FVector Location, const ESoundUse Type, const FName SubType,
	const FName Map, const float StartTime)
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
		GetWorld(),
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

void USoundSubsystem::StopMusic()
{
	if (CurrentMusicComponent.IsValid())
	{
		CurrentMusicComponent.Pin()->Stop();
		CurrentMusicComponent = nullptr;
	}
}

void USoundSubsystem::GetRandomSound(TArray<FSoundRow*>& Rows, const ESoundUse Type, const FName& SubType,
	const FName& Map) const
{
	SoundDataTable->GetAllRows<FSoundRow>("", Rows);
	FilterRows(Rows, Type, SubType, Map);
}

void USoundSubsystem::PlayAmbientSoundBlend(const USoundCue* Sound, const float StartTime, float BlendSpeed,
	USoundConcurrency* Concurrency, const float PitchMultiplier)
{
		
	USettingsSave* Save = Cast<USettingsSave>(UGameplayStatics::LoadGameFromSlot("settings", 0));
	BlendMusicDown(BlendSpeed, AmbientComponent);
	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, "BlendAmbientIn", Sound, 
		Save->MusicVolume, PitchMultiplier, 
		StartTime, Concurrency, BlendSpeed);
	FTimerHandle DelegateHandle;
	GetWorld()->GetTimerManager().SetTimer(DelegateHandle, Delegate, BlendSpeed, false);
}

void USoundSubsystem::SyncVolume() const
{
	if (CurrentMusicComponent.IsValid())
	{
		USettingsSave* Save = Cast<USettingsSave>(UGameplayStatics::LoadGameFromSlot("settings", 0));
		CurrentMusicComponent.Pin()->SetVolumeMultiplier(Save->MusicVolume);
	}
}

void USoundSubsystem::PlayRandomMusicBlend(const FName SubType, const FName Map, const float StartTime, const float BlendSpeed)
{
	BlendMusicDown(BlendSpeed);
	TArray<FSoundRow*> Rows;
	GetRandomSound(Rows, ESoundUse::Music, SubType, Map);

	if (Rows.Num() == 0)
	{
		return;
	}

	int SoundIndex = FMath::RandRange(0, Rows.Num() -1);

	USettingsSave* Save = Cast<USettingsSave>(UGameplayStatics::LoadGameFromSlot("settings", 0));
	
	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, "BlendMusicIn", Rows[SoundIndex]->Sound, 
		Save->MusicVolume, Rows[SoundIndex]->PitchMultiplier, 
		StartTime, Rows[SoundIndex]->Concurrency, BlendSpeed);
	FTimerHandle DelegateHandle;
	
	GetWorld()->GetTimerManager().SetTimer(DelegateHandle, Delegate, BlendSpeed, false);
}

void USoundSubsystem::PlaySoundBlend(const TArray<USoundCue*>& Sound, const float StartTime, float BlendSpeed,
	USoundConcurrency* Concurrency, const float PitchMultiplier)
{
	USettingsSave* Save = Cast<USettingsSave>(UGameplayStatics::LoadGameFromSlot("settings", 0));
	
	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, "BlendMusicIn", Sound, 
		Save->MusicVolume, PitchMultiplier, 
		StartTime, Concurrency, BlendSpeed);
	FTimerHandle DelegateHandle;
	GetWorld()->GetTimerManager().SetTimer(DelegateHandle, Delegate, BlendSpeed, false);
}

void USoundSubsystem::BlendOutSound(USoundCue* Sound, float BlendSpeed)
{
	for (auto& comp : MusicComponents)
	{
		if (!comp.IsValid()) continue;
		if (comp->GetSound() != Sound) continue;
		comp->FadeOut(BlendSpeed, 0);
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "DereferenceSound", Sound);
		FTimerHandle DelegateHandle;
		GetWorld()->GetTimerManager().SetTimer(DelegateHandle, Delegate, BlendSpeed, false);
	}
}

bool USoundSubsystem::IsMatchingType(const FSoundRow* row, const ESoundUse Type)
{
	return row->Type == Type || row->Type == ESoundUse::Any;
}

bool USoundSubsystem::IsMatchingSubType(const FSoundRow* row, const FName SubType)
{
	return SubType == "None" || SubType == row->SubType;
}

bool USoundSubsystem::IsMatchingMap(const FSoundRow* row, const FName Map)
{
	return Map == "None" || Map == row->Map;
}

void USoundSubsystem::FilterRows(TArray<FSoundRow*>& Rows, const ESoundUse Type, const FName& SubType, const FName& Map)
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



void USoundSubsystem::BlendMusicDown(const float BlendSpeed, TWeakObjectPtr<UAudioComponent> Comp)
{
	if (Comp.IsValid())
	{
		Comp->FadeOut(BlendSpeed, 0);
	}
}


void USoundSubsystem::BlendMusicDown(const float BlendSpeed) const
{
	if (CurrentMusicComponent.IsValid())
	{
		CurrentMusicComponent->FadeOut(BlendSpeed, 0);
	}
}

void USoundSubsystem::BlendMusicIn(USoundCue* Sound, const float Volume, const float PitchMultiplier,
                                   const float StartTime, USoundConcurrency* Concurrency, const float BlendSpeed)
{
	CurrentMusicComponent = TWeakObjectPtr<UAudioComponent>(UGameplayStatics::CreateSound2D
	(
		GetWorld(),
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

void USoundSubsystem::BlendAmbientIn(USoundCue* Sound, const float Volume, const float PitchMultiplier,
								   const float StartTime, USoundConcurrency* Concurrency, const float BlendSpeed)
{
	CurrentMusicComponent = TWeakObjectPtr<UAudioComponent>(UGameplayStatics::CreateSound2D
	(
		GetWorld(),
		Sound,
		Volume,
		PitchMultiplier,
		StartTime,
		Concurrency,
	false,
	true
	));
	AmbientComponent.Pin()->FadeIn(BlendSpeed, Volume);
}

void USoundSubsystem::BlendMusicInMulti(const TArray<USoundCue*>& Sound, const float Volume,
	const float PitchMultiplier, const float StartTime, USoundConcurrency* Concurrency, float BlendSpeed)
{
	for (USoundCue* sound : Sound)
	{
		MusicComponents.Add(TWeakObjectPtr<UAudioComponent>(UGameplayStatics::CreateSound2D
			(
			GetWorld(),
			sound,
			Volume,
			PitchMultiplier,
			StartTime,
			Concurrency,
		false,
		true
			))
		);
		CurrentMusicComponent.Pin()->FadeIn(BlendSpeed, Volume);
	}
}

void USoundSubsystem::DereferenceSound(USoundCue* Sound)
{
	for (auto& comp : MusicComponents)
	{
		if (!comp.IsValid()) continue;
		if (comp->GetSound() != Sound) continue;
		MusicComponents.Remove(comp);
		return;
	}
}
