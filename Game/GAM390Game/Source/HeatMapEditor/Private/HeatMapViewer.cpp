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
	Load2DHeatMapsButton->OnClicked.AddDynamic(this, &UHeatMapViewer::LoadHeatMaps2D);
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
	SelectHeatMapFiles();
	TArray<FVector> playerPositions;
	LoadHeatMapFiles(playerPositions);
	LoadHeatMap(playerPositions);
}

void UHeatMapViewer::LoadHeatMaps2D()
{
	SelectHeatMapFiles();
	TArray<FVector> playerPositions;
	LoadHeatMapFiles(playerPositions);
	Load2DHeatMaps(playerPositions);
}

void UHeatMapViewer::Load2DHeatMaps(const TArray<FVector>& PlayerPositions)
{
	const FVector size = GridSquare.GetDefaultObject()->GetMeshBounds();
	
	TArray<FGridInfo> HeatSpots;
	
	uint32 highestTimes = CalculateGridInfoForPositions2D(PlayerPositions, size, HeatSpots);

	FVector2D min = {-5000, -5110};
	FVector2D max = {4900, 4800};
	FVector2D dif = max - min;
	FVector2D lengthOfOnePoint = {1024 / dif.X, 1024 / dif.Y};
	mat = UMaterialInstanceDynamic::Create(HeatMapMaterial, this);
	UE_LOG(LogTemp, Warning, TEXT("POS, %0.5f, %0.5f"), lengthOfOnePoint.X, lengthOfOnePoint.Y);


	FTimerHandle handle;
	FTimerDelegate del;


	del.BindUFunction(this, "Test", 0, HeatSpots);

	GetWorld()->GetTimerManager().SetTimerForNextTick(del);



}

void UHeatMapViewer::Test(uint32 index, TArray<FGridInfo> HeatSpots)
{
	FVector2D min = { -5000, -5110 };
	FVector2D max = { 4900, 4800 };
	FVector2D dif = max - min;
	FVector2D lengthOfOnePoint = { 1024 / dif.X, 1024 / dif.Y };

	FVector2D pos = FVector2D(HeatSpots[index].IndexPosition) * lengthOfOnePoint;
	FVector2D start = max / dif;
	pos /= dif;
	pos = start + pos;

	mat->SetVectorParameterValue("Position", FVector(pos, 0));
	mat->SetScalarParameterValue("Strength", HeatSpots[index].NumTimes);
	index++;
	UKismetRenderingLibrary::DrawMaterialToRenderTarget(GetWorld(), HeatMapRenderTarget, mat);
	if (index == HeatSpots.Num()) {

		return;
	}


	FTimerHandle handle;
	FTimerDelegate del;


	del.BindUFunction(this, "Test", index, HeatSpots);

	GetWorld()->GetTimerManager().SetTimerForNextTick(del);




}

uint32 UHeatMapViewer::CalculateGridInfoForPositions(const TArray<FVector>& PlayerPositions, const FVector& Size, TArray<FGridInfo>& HeatSpots)
{
	uint32 highestTimes = 1;
	for (auto& pos : PlayerPositions)
	{
		float xIndex = static_cast<int32>(pos.X) / Size.X;
		float yIndex = static_cast<int32>(pos.Y) / Size.Y;
		float zIndex = static_cast<int32>(pos.Z) / Size.Z;

		FGridInfo info = {{xIndex, yIndex, zIndex}, 1};

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

uint32 UHeatMapViewer::CalculateGridInfoForPositions2D(const TArray<FVector>& PlayerPositions, const FVector& Size, TArray<FGridInfo>& HeatSpots)
{
	uint32 highestTimes = 1;
	for (auto& pos : PlayerPositions)
	{
		FVector2D min = {-5000, -5110};
		FVector2D newPos = FVector2D(pos);
		FGridInfo info = {FVector(newPos, 0), 1};

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

void UHeatMapViewer::LoadHeatMapFiles(TArray<FVector>& PlayerPositions)
{
	for (FString& fileName: FileNames)
	{
		fileName = GetSavePath(fileName);
		if (UGameplayStatics::DoesSaveGameExist(fileName, 0))
		{
			UHeatMapData* Data = Cast<UHeatMapData>(UGameplayStatics::LoadGameFromSlot(fileName, 0));
			PlayerPositions.Append(Data->PlayerPositions);
		}
	}
}

void UHeatMapViewer::SelectHeatMapFiles()
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
	}
}

void UHeatMapViewer::LoadHeatMap(const TArray<FVector>& PlayerPositions)
{
	const FVector size = GridSquare.GetDefaultObject()->GetMeshBounds();
	
	TArray<FGridInfo> HeatSpots;
	
	uint32 highestTimes = CalculateGridInfoForPositions(PlayerPositions, size, HeatSpots);

	for (size_t i = 0; i < HeatSpots.Num(); i++)
	{
		FActorSpawnParameters spawnInfo;

		FGridInfo& heatSpot = HeatSpots[i];
		
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
