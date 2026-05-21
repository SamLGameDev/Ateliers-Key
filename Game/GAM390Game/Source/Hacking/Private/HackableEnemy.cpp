// Fill out your copyright notice in the Description page of Project Settings.


#include "HackableEnemy.h"
#include "Components/DecalComponent.h"
#include "Hacks/HackEffect.h"
#include "GUI_HackProgress.h"

// Sets default values
AHackableEnemy::AHackableEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	LoadingBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("LoadingBar"));
	LoadingBar->SetupAttachment(Root);

	DisableHighlight();

	DisableLoadingBar();
}


// Called when the game starts or when spawned
void AHackableEnemy::BeginPlay()
{
	Super::BeginPlay();

	GetComponents<UMeshComponent>(BaseMesh);
	if (HackableObjects)
	{
		HackableObjects->RegisterObject(this);
	}
}

// Called every frame
void AHackableEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHackableEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
