// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "GUI_HackSelector.generated.h"

class UGUB_HackingButton;
class UHackEffectStore;

/**
 * 
 */
UCLASS()
class HACKING_API UGUI_HackSelector : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere,meta=(BindWidget))
	UScrollBox* AvaialableHacksDisplay;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGUB_HackingButton* HackingButton1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGUB_HackingButton* HackingButton2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGUB_HackingButton* HackingButton3;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGUB_HackingButton* HackingButton4;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGUB_HackingButton* HackingButton5;

	TArray<UGUB_HackingButton*> ButtonSlots;

	int CurrentButtonSlot = 0;

	void FocusNextSlot();

	void FocusPreviousSlot();

	TArray<UGUB_HackingButton*> AvailableHackButtons;

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly)
	UHackEffectStore* AvailableHacks;

	int CurrentAvailableHack;

	void FocusNextAvailableHack();

	void FocusPreviousAvailableHack();

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* SlotHackDescription;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* PotentialHackDescription;

	
};
