// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "GUI_DamageLocationIndicator.generated.h"

/**
 * 
 */
UCLASS()
class GAM390GAME_API UGUI_DamageLocationIndicator : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void RotateToFace(const FVector Direction);
private:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UCanvasPanel* Canvas;
};
