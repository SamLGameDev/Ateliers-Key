// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FeedbackSettings.generated.h"

/**
 * 
 */
UCLASS(config=Game, defaultconfig, meta=(DisplayName="Feedback Settings"))
class GENERALUTILITIES_API UFeedbackSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, config, Category="Version", meta=(DisplayName="Game Version"))
	FString VersionName = TEXT("1.1.0");
	
	virtual FName GetCategoryName() const override { return TEXT("Game"); }
};
