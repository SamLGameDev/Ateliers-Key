// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GUI_HackingMenu.generated.h"

class UScrollBox;
class UGUB_HackingButton;
class UHackEffect;
class UTextBlock;
class UBorder;

/**
 * 
 */
UCLASS()
class HACKING_API UGUI_HackingMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void FocusNextHackButton();

	UFUNCTION()
	void FocusPreviousHackButton();

	void UpdateButtonDisplay(const TArray<UHackEffect*>& Hacks);

	void DisableHackButtons();

	void SetFocusedObject(UObject* Object)
	{
		FocusedObject = Object;
	}

	void TriggerHack();

	const bool IsHacking() const
	{
		return bIsHacking;
	}

	void SetHackingStarted();

	void SetHackingEnded();

private:

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

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* HackDescription;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UBorder* HackDescriptionParent;

	bool bIsHacking = false;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	int CurrentlyFocused = 0;

	int EnabledButtons;

	UObject* FocusedObject;

	TArray<UGUB_HackingButton*> HackingButtons;





};
