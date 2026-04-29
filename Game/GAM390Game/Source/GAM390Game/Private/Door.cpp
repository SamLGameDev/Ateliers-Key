// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "BP_GeneralFunctions.h"
#include "Components/SplineComponent.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
ADoor::ADoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("m_RootComp"));
	RootComponent = m_RootComp;

	Path = CreateDefaultSubobject<USplineComponent>(TEXT("Path"));
	Path->SetupAttachment(RootComponent);

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_Mesh->SetupAttachment(RootComponent);
}

float const ADoor::Fall(const TArray<UStaticMeshComponent*> DoorsToMove)
{
	FTimerDelegate params;
	params.BindUFunction(this, NAMEOF(MoveMeshTowardsEnd), 0);
	GetWorld()->GetTimerManager().SetTimerForNextTick(params);
	return Path->GetSplineLength() / m_Speed;
}


void ADoor::MoveMeshTowardsEnd(const float alpha)
{
	FTransform EndPos;
	if (Path)
	{
		const FVector currentPos = m_Mesh->GetComponentLocation();
		EndPos = Path->GetTransformAtDistanceAlongSpline(alpha, ESplineCoordinateSpace::World);
	}
	if (Path && EndPos.IsValid()) {
		m_Mesh->SetWorldLocation(EndPos.GetLocation());;
	}
	if (alpha >= Path->GetSplineLength()) return;
	
	FTimerDelegate params;
	params.BindUFunction(this, NAMEOF(MoveMeshTowardsEnd), alpha + (m_Speed * GetWorld()->GetDeltaSeconds()));
	GetWorld()->GetTimerManager().SetTimerForNextTick(params);
}


