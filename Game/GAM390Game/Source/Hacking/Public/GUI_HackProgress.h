// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GUI_HackProgress.generated.h"

class UProgressBar;

/**
 * 
 */
UCLASS()
class HACKING_API UGUI_HackProgress : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetFill(float InPercent);

private:

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UProgressBar* LoadingBar;


	
};
