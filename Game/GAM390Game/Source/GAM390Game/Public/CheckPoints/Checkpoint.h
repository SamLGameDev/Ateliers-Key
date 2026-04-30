// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseVariableStore.h"
#include "Components/BoxComponent.h"
#include "Checkpoint.generated.h"

class ABP_Player;

UCLASS()
class GAM390GAME_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint();

	UFUNCTION(BlueprintCallable)
	void SetAsCurrentCheckpoint(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION(BlueprintCallable)
	void SaveToSlot(ABP_Player* Player);

	UPROPERTY(EditInstanceOnly)
	ACheckpoint* NextCheckpoint;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* CollisionZone;

	UPROPERTY(EditInstanceOnly)
	TSoftObjectPtr<UWorld> CombatEncounter;
	UPROPERTY(EditInstanceOnly)
	TArray<TSoftObjectPtr<UWorld>> WorldsToLoad;

public:	



};
