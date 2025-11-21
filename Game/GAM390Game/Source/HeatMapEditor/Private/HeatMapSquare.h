// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeatMapSquare.generated.h"

UCLASS()
class HEATMAPEDITOR_API AHeatMapSquare : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHeatMapSquare();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DisplayCube;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* HeatMapMaterial;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetHeatMapColor(FLinearColor Color);

	UFUNCTION()
	FVector GetMeshBounds();
};
