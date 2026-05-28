// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DiscordTriggerVolume.generated.h"

class UBoxComponent;

UCLASS()
class ATELIERSKEY_API ADiscordTriggerVolume : public AActor
{
	GENERATED_BODY()
	
public:
	ADiscordTriggerVolume();

protected:
	virtual void BeginPlay() override;
	void UpdatePresence();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision")
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Discord")
	FString Details;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
};