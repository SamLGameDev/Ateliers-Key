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
class ATELIERSKEY_API UGUI_DamageLocationIndicator : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
	virtual void RotateToFace(const FVector Direction, const FVector ForwardDir, const FVector UpDir);

	UFUNCTION()
	virtual void SetHidden();

	UFUNCTION()
	virtual void SetVisible();

	UFUNCTION()
	virtual void StartRotation(const AActor* Source, const AActor* Hit, TArray<UGUI_DamageLocationIndicator*>& UnusedIndicators, const float FadeTime);

	UFUNCTION()

	void TickRotation(const AActor* Source, const AActor* Hit);

	UFUNCTION()
	virtual void EndRotation(TArray<UGUI_DamageLocationIndicator*>& UnusedIndicators);

	FTimerHandle TickHandle;

	FTimerHandle FadeHandle;
private:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UCanvasPanel* Canvas;
};
