// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HeatMapData.generated.h"

/**
 * 
 */
UCLASS()
class HEATMAP_API UHeatMapData : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heat Map Data")
	TArray<FVector> PlayerPositions;
	
};
