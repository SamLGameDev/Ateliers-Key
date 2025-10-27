// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BP_UserWidgetFunctions.generated.h"

class UAUW_BaseMenuWidget;

/**
 * 
 */
UCLASS()
class MENUS_API UBP_UserWidgetFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	static void ChangeWidget(UAUW_BaseMenuWidget* Current, UAUW_BaseMenuWidget* NewWidget);


private:
};
