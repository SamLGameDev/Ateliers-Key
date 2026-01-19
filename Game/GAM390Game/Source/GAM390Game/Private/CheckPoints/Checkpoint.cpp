// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckPoints/Checkpoint.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	CollisionZone = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionZone"));

	CollisionZone->SetupAttachment(RootComponent);

	CollisionZone->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::SetAsCurrentCheckpoint);
}

void ACheckpoint::SetAsCurrentCheckpoint(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FCheckpointInfo checkpoint;
	checkpoint.RestartTransform = FTransform(GetActorRotation(), GetActorLocation(), FVector(1, 1, 1));

	CurrentCheckpoint->SetObject(checkpoint);

	Destroy();
}