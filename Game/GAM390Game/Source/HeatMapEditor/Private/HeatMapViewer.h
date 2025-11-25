// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"
#include "HeatMapData.h"
#include "Editor/Blutility/Classes/EditorUtilityWidgetComponents.h"
#include "Components/TextBlock.h"
#include "HeatMapViewer.generated.h"


class AHeatMapSquare;

USTRUCT()
struct FGridInfo
{
	GENERATED_BODY()
	FVector IndexPosition;
	uint32 NumTimes;

	bool operator==(const FGridInfo& Other) const
	{
		return IndexPosition == Other.IndexPosition;
	}
};

/**
 * 
 */
UCLASS()
class HEATMAPEDITOR_API UHeatMapViewer : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UEditorUtilityButton* LoadHeatMapsButton;

	UPROPERTY(meta=(BindWidget))
	UEditorUtilityButton* Load2DHeatMapsButton;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* test;

	void NativeConstruct() override;

	void NativeDestruct() override;
	FString GetSavePath(const FString& fileName);

	UFUNCTION()
	void LoadHeatMaps();

	UFUNCTION()
	void LoadHeatMaps2D();

	UFUNCTION()
	void Load2DHeatMaps(const TArray<FVector>& PlayerPositions);

	UFUNCTION()
	void LoadHeatMap(const TArray<FVector>& PlayerPositions);

	static uint32 CalculateGridInfoForPositions(const TArray<FVector>& PlayerPositions, const FVector& Size, TArray<FGridInfo>& HeatSpots);
	static uint32 CalculateGridInfoForPositions2D(const TArray<FVector>& PlayerPositions, const FVector& Size, TArray<FGridInfo>& HeatSpots);

	void LoadHeatMapFiles(TArray<FVector>& PlayerPositions);
	
	void SelectHeatMapFiles();
	
	UPROPERTY(EditAnywhere)
	uint32 GridSize;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AHeatMapSquare> GridSquare;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor LowestColor;
	UPROPERTY(EditDefaultsOnly)
	FLinearColor SecondLowestColor;
	UPROPERTY(EditDefaultsOnly)
	FLinearColor SecondHighestColor;
	UPROPERTY(EditDefaultsOnly)
	FLinearColor HighestColor;

	TArray<FString> FileNames;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* HeatMapMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* HeatMapColor;

	UPROPERTY(EditDefaultsOnly)
	UTextureRenderTarget2D* HeatMapRenderTarget;

	UMaterialInstanceDynamic* BaseDrawMaterial;
	UMaterialInstanceDynamic* ColorDrawMaterial;

	UPROPERTY(EditDefaultsOnly)
	UTextureRenderTarget2D*	ColorHeatMapRenderTarget;

	void GetMapBounds(FVector2D& Min, FVector2D& Max);
	
	FVector2D MapBoundsMin = FVector2D(FLT_MAX, FLT_MAX);

	FVector2D MapBoundsMax = FVector2D(-FLT_MAX, -FLT_MAX);
	
};
