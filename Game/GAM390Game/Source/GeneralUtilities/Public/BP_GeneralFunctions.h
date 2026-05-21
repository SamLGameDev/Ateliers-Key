// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BP_GeneralFunctions.generated.h"

#define NAMEOF(name) #name

#if UE_BUILD_DEBUG || WITH_EDITOR
#define Print(message, ...) UE_LOG(LogTemp, Warning, TEXT(message), __VA_ARGS__);
#endif

/**
 * 
 */
UCLASS()
class GENERALUTILITIES_API UBP_GeneralFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	static void SetToGameplayControls(APlayerController* Controller);

	UFUNCTION(BlueprintCallable)
	static void SetToMenuControls(APlayerController* Controller);

	DECLARE_DELEGATE_OneParam(FInterfaceSignature, AActor*)

	static FInterfaceSignature InterfaceDelegate;
	
};
