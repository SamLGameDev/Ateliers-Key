// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "GUI_HackSelector.generated.h"

class UGUB_HackSelectionButton;
class UHackEffectStore;

/**
 * 
 */
UCLASS()
class HACKING_API UGUI_HackSelector : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void FocusNextSlot();

	UFUNCTION()
	void FocusPreviousSlot();


	UFUNCTION()
	void FocusNextAvailableHack();

	UFUNCTION()
	void FocusPreviousAvailableHack();


	UFUNCTION()
	void LoadSelectedToSlot();


	UFUNCTION()
	void Exit();

private:

	UPROPERTY(EditAnywhere,meta=(BindWidget))
	UScrollBox* AvaialableHacksDisplay;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGUB_HackSelectionButton* HackingButton1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGUB_HackSelectionButton* HackingButton2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGUB_HackSelectionButton* HackingButton3;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGUB_HackSelectionButton* HackingButton4;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGUB_HackSelectionButton* HackingButton5;

	TArray<UGUB_HackSelectionButton*> ButtonSlots;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGUB_HackSelectionButton> BPHackingButton;

	int CurrentButtonSlot = 0;



	TArray<UGUB_HackSelectionButton*> AvailableHackButtons;

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly)
	UHackEffectStore* AvailableHacks;

	int CurrentAvailableHack;


	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* SlotHackDescription;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* PotentialHackDescription;



	UPROPERTY(EditDefaultsOnly)
	UHackEffectStore* LoadedHacks;

	
};
