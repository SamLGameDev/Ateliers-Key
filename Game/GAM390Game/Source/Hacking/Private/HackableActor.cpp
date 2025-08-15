// Fill out your copyright notice in the Description page of Project Settings.


#include "HackableActor.h"
#include "Components/DecalComponent.h"
#include "Hacks/HackEffect.h"
#include "ActorList.h"
#include "Components/WidgetComponent.h"
#include "GUI_HackProgress.h"

// Sets default values
AHackableActor::AHackableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	LoadingBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("LoadingBar"));
	LoadingBar->SetupAttachment(Root);


	DisableHighlight();

	DisableLoadingBar();
}

// Called when the game starts or when spawned
void AHackableActor::BeginPlay()
{
	Super::BeginPlay();

	GetComponents<UMeshComponent>(BaseMesh);

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

