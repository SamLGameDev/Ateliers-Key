// Fill out your copyright notice in the Description page of Project Settings.


#include "HeatMapSquare.h"

#include "ShaderCompiler.h"
#include "Widgets/Images/SThrobber.h"


// Sets default values
AHeatMapSquare::AHeatMapSquare()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DisplayCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DisplayCube"));
}

// Called when the game starts or when spawned
void AHeatMapSquare::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHeatMapSquare::SetHeatMapColor(FLinearColor Color)
{
	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(HeatMapMaterial, this);
	DynamicMaterial->SetVectorParameterValue(FName("Color"), Color);

	DisplayCube->SetMaterial(0, DynamicMaterial);
}

FVector AHeatMapSquare::GetMeshBounds()
{
	FVector min, max;
	DisplayCube->GetLocalBounds(min, max);
	return max - min;
}

// Called every frame
void AHeatMapSquare::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

