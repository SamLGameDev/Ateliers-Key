// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CommonUIHelpers.generated.h"

/**
 * 
 */
UCLASS()
class GAM390GAME_API UCommonUIHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "CommonUIHelpers", meta = (WorldContext = WorldContextObject))
	static void SimulateUIMouseClickAtCursor(UObject* WorldContextObject);

	
	/**
	 * Generates a click event at screen space 0, 0
	 * @param WorldContextObject 
	 */
	UFUNCTION(BlueprintCallable, Category = "CommonUIHelpers", meta = (WorldContext = WorldContextObject))
	static void SimulateUIMouseClick(UObject* WorldContextObject);
};
