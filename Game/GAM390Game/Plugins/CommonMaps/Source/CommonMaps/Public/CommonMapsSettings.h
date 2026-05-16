// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "CommonMapsSettings.generated.h"

UCLASS(Config=Game, defaultconfig, meta=(DisplayName="Common Maps Settings"))
class COMMONMAPS_API UCommonMapsSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UCommonMapsSettings()
	{
		CategoryName = TEXT("Plugins");
		SectionName  = TEXT("Common Maps");

		AssetSearchPath.Path = TEXT("/Game");
	}

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Asset Paths",
		meta=(DisplayName="Asset Search Path", LongPackageName))
	FDirectoryPath AssetSearchPath;

	UFUNCTION(BlueprintPure, BlueprintCallable, Category="Common Maps|Settings")
	static FString GetAssetSearchPath()
	{
		const UCommonMapsSettings* Settings = GetDefault<UCommonMapsSettings>();
		return Settings ? Settings->AssetSearchPath.Path : FString(TEXT("/Game"));
	}
};