// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GUB_HackingButton.generated.h"

class UButton;
class UTextBlock;
struct FButtonStyle;
class UHackEffect;
class AHackableActor;

/**
 * 
 */
UCLASS()
class HACKING_API UGUB_HackingButton : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget), BlueprintReadWrite)
	UButton* Clickable;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* DisplayText;

	void SetFocused();

	void SetUnFocused();

	void SetHack(UHackEffect* Hack);

	UPROPERTY(EditAnywhere)
	FButtonStyle FocusedStyle;
	
	UPROPERTY(EditAnywhere)
	FButtonStyle UnFocusedStyle;

	void StartHack(UObject* HackedObject);

	UFUNCTION()
	void ProgressHack(AHackableActor* HackedObject, float TimeRemaining);

	void TriggerHack(AHackableActor* HackedObject);

private:
	UHackEffect* LoadedEffect;
};
