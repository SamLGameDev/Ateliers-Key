// Fill out your copyright notice in the Description page of Project Settings.


#include "GrenadeExplosion.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "DamageSystem.h"

// Sets default values
AGrenadeExplosion::AGrenadeExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGrenadeExplosion::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGrenadeExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

