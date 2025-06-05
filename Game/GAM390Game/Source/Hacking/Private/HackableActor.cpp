// Fill out your copyright notice in the Description page of Project Settings.


#include "HackableActor.h"
#include "Components/DecalComponent.h"
#include "ActorList.h"

// Sets default values
AHackableActor::AHackableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	DisableHighlight();
}

void AHackableActor::EnableHighlight()
{
	Mesh->SetOverlayMaterial(HackableObejctOutline);
}

void AHackableActor::DisableHighlight()
{
	Mesh->SetOverlayMaterial(nullptr);
}

// Called when the game starts or when spawned
void AHackableActor::BeginPlay()
{
	Super::BeginPlay();

	if(HackableObjects)
	{
		HackableObjects->RegisterObject(this);
	}
}

// Called every frame
void AHackableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

