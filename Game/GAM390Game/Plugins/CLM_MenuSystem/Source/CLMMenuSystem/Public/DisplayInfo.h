// CodeLikeMe Menu System - (c) 2025 CodeLikeMe GmbH

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DisplayInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CLMMENUSYSTEM_API FDisplayInfo
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString Name;

	UPROPERTY(BlueprintReadOnly)
	FString ID;

	UPROPERTY(BlueprintReadOnly)
	int32 NativeWidth = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 NativeHeight = 0;

	UPROPERTY(BlueprintReadOnly)
	FIntPoint MaxResolution = FIntPoint(ForceInitToZero);

	UPROPERTY(BlueprintReadOnly)
	bool bIsPrimary = false;

	UPROPERTY(BlueprintReadOnly)
	int32 DPI = 0;


	// Default constructor 
	FDisplayInfo()
	{
		Name = FString("");
		ID = FString("");
		NativeWidth = 0;
		NativeHeight = 0;
		MaxResolution = FIntPoint(ForceInitToZero);
		bIsPrimary = false;
		DPI = 0;
	}

	//Custom constructor 
	FDisplayInfo(const FString& InName, const FString& InID, int32 InNativeWidth, int32 InNativeHeight,
		const FIntPoint& InMaxResolution, bool InIsPrimary, int32 InDPI)
		: Name(InName),
		ID(InID),
		NativeWidth(InNativeWidth),
		NativeHeight(InNativeHeight),
		MaxResolution(InMaxResolution),
		bIsPrimary(InIsPrimary),
		DPI(InDPI)
	{
	}
};
