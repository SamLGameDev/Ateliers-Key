// Fill out your copyright notice in the Description page of Project Settings.


#include "HeatMapViewer.h"

#include "AnalyticsBuildType.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Kismet/GameplayStatics.h"
#include "HeatMapSquare.h"

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

		TArray<FString> FileNames;

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

		for (FString& fileName: FileNames)
		{
			fileName = "HeatMaps/"+ FPaths::GetBaseFilename(fileName);
			if (UGameplayStatics::DoesSaveGameExist(fileName, 0))
			{
				LoadHeatMap(fileName);
			}
		}
	}
}

void UHeatMapViewer::LoadHeatMap(const FString& MapToLoad)
{
	const FVector size = GridSquare.GetDefaultObject()->GetMeshBounds();
	
	TArray<GridInfo> HeatSpots;

	UHeatMapData* Data = Cast<UHeatMapData>(UGameplayStatics::LoadGameFromSlot(MapToLoad, 0));

	uint32 highestTimes = 1;

	for (auto& pos : Data->PlayerPositions)
	{
		int32 xIndex = static_cast<int32>(pos.X) / size.X;
		int32 yIndex = static_cast<int32>(pos.Y) / size.Y;
		int32 zIndex = static_cast<int32>(pos.Z) / size.Z;

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