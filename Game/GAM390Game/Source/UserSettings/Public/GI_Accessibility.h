// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GI_Accessibility.generated.h"

/**
 * rename from GI_Accessibility, but references are still that, so you might be looking for that
 */
UCLASS()
class USERSETTINGS_API UGI_SanctumSettings : public UGameInstance
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSubtitlesEnabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int m_SubtitleSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_Brightness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ControllerVibration;

	UPROPERTY(BlueprintReadOnly)
	float CameraSensitivity;

	UPROPERTY(BlueprintReadOnly)
	float CameraFov;

	virtual void Init() override;

	void SyncSubtitlesSettings();
	
};
