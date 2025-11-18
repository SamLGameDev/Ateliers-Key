// Fill out your copyright notice in the Description page of Project Settings.


#include "HeatMapViewer.h"

#include "AnalyticsBuildType.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Kismet/GameplayStatics.h"
#include "HeatMapSquare.h"
#include "Kismet/KismetRenderingLibrary.h"

void UHeatMapViewer::NativeConstruct()
{
	Super::NativeConstruct();

	LoadHeatMapsButton->OnClicked.AddDynamic(this, &UHeatMapViewer::LoadHeatMaps);
}

void UHeatMapViewer::NativeDestruct()
{
	Super::NativeDestruct();
	TArray<AActor*> Results;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), GridSquare, Results);
	for (auto* actor : Results)
	{
		actor->Destroy();
	}
}

FString UHeatMapViewer::GetSavePath(const FString& fileName)
{
	return "HeatMaps/" + FPaths::GetBaseFilename(fileName);
}

void UHeatMapViewer::LoadHeatMaps()
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();

	if (DesktopPlatform)
	{
		void* ParentWindowHandle = nullptr;
		if (FSlateApplication::IsInitialized())
		{
			TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().FindBestParentWindowForDialogs(nullptr); 
			ParentWindowHandle = ParentWindow.IsValid() ? ParentWindow->GetNativeWindow()->GetOSWindowHandle() : nullptr;
		}
		

		FString DefaultPath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("SaveGames/HeatMaps"));
		IFileManager::Get().MakeDirectory(*DefaultPath, true);
		
		DesktopPlatform->OpenFileDialog(
			ParentWindowHandle,
			"",
			DefaultPath,
			TEXT(""),
			TEXT("Save Files (*.sav)|*.sav"),
			EFileDialogFlags::Multiple,
			FileNames
		);

		TArray<FVector> playerPositions;
		for (FString& fileName: FileNames)
		{
			fileName = GetSavePath(fileName);
			if (UGameplayStatics::DoesSaveGameExist(fileName, 0))
			{
				UHeatMapData* Data = Cast<UHeatMapData>(UGameplayStatics::LoadGameFromSlot(fileName, 0));
				playerPositions.Append(Data->PlayerPositions);
			}
		}
		LoadHeatMap(playerPositions);
	}
}

void UHeatMapViewer::Load2DHeatMaps(const TArray<FVector>& PlayerPositions)
{
	const FVector size = GridSquare.GetDefaultObject()->GetMeshBounds();
	
	TArray<GridInfo> HeatSpots;
	
	uint32 highestTimes = CalculateGridInfoForPositions2D(PlayerPositions, size, HeatSpots);

	for (size_t i = 0; i < HeatSpots.Num(); i++)
	{
		
		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(HeatMapMaterial, this);
		DynamicMaterial->SetVectorParameterValue("Position", HeatSpots[i].IndexPosition);
		DynamicMaterial->SetScalarParameterValue("Strength", HeatSpots[i].NumTimes);
		UKismetRenderingLibrary::DrawMaterialToRenderTarget(GetWorld(), HeatMapRenderTarget, DynamicMaterial);
	}
}

uint32 UHeatMapViewer::CalculateGridInfoForPositions(const TArray<FVector>& PlayerPositions, const FVector& Size, TArray<GridInfo>& HeatSpots)
{
	uint32 highestTimes = 1;
	for (auto& pos : PlayerPositions)
	{
		float xIndex = static_cast<int32>(pos.X) / Size.X;
		float yIndex = static_cast<int32>(pos.Y) / Size.Y;
		float zIndex = static_cast<int32>(pos.Z) / Size.Z;

		GridInfo info = {{xIndex, yIndex, zIndex}, 1};

		int index = 0;
		if (HeatSpots.Find(info, index))
		{
			HeatSpots[index].NumTimes += 1;
			if (HeatSpots[index].NumTimes > highestTimes)
			{
				highestTimes = HeatSpots[index].NumTimes;
			}
		}
		else
		{
			HeatSpots.Add(info);
		}	
	}
	return highestTimes;
}

uint32 UHeatMapViewer::CalculateGridInfoForPositions2D(const TArray<FVector>& PlayerPositions, const FVector& Size, TArray<GridInfo>& HeatSpots)
{
	uint32 highestTimes = 1;
	for (auto& pos : PlayerPositions)
	{

		GridInfo info = {{pos.X, pos.Y, 0}, 1};

		int index = 0;
		if (HeatSpots.Find(info, index))
		{
			HeatSpots[index].NumTimes += 1;
			if (HeatSpots[index].NumTimes > highestTimes)
			{
				highestTimes = HeatSpots[index].NumTimes;
			}
		}
		else
		{
			HeatSpots.Add(info);
		}	
	}
	return highestTimes;
}

void UHeatMapViewer::LoadHeatMap(const TArray<FVector>& PlayerPositions)
{
	const FVector size = GridSquare.GetDefaultObject()->GetMeshBounds();
	
	TArray<GridInfo> HeatSpots;
	
	uint32 highestTimes = CalculateGridInfoForPositions(PlayerPositions, size, HeatSpots);

	for (size_t i = 0; i < HeatSpots.Num(); i++)
	{
		FActorSpawnParameters spawnInfo;

		GridInfo& heatSpot = HeatSpots[i];
		
		spawnInfo.Name = NAME_None;
		spawnInfo.bNoFail = true;

		const FVector pos = (FVector(heatSpot.IndexPosition) * size) + size / 2.f;
		
		AHeatMapSquare* square = GetWorld()->SpawnActor<AHeatMapSquare>(GridSquare, pos, FRotator::ZeroRotator, spawnInfo );
		
		const float heatLevel = static_cast<float>(heatSpot.NumTimes) / highestTimes;

		FLinearColor color = FLinearColor::White;

		UE_LOG(LogTemp, Warning, TEXT("HeatMapSquare created %d, Highest: %d"), heatSpot.NumTimes, highestTimes);
		
		if (heatLevel <= 0.33f)
		{
			color = FLinearColor::LerpUsingHSV(LowestColor, SecondLowestColor, heatLevel / 0.33f);
		}
		else if (heatLevel <= 0.66f)
		{
			color = FLinearColor::LerpUsingHSV(SecondLowestColor, SecondHighestColor, heatLevel / 0.66f);
		}
		else if (heatLevel <= 1.f)
		{
			color = FLinearColor::LerpUsingHSV(SecondHighestColor, HighestColor, heatLevel);
		}
		
		square->SetHeatMapColor(color);
	}
	
}
