// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI_HackingMenu.h"
#include "Components/ScrollBox.h"
#include "GUB_HackingButton.h"
#include "Hacks/HackEffect.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"

void UGUI_HackingMenu::FocusNextHackButton()
{
	if (CurrentlyFocused < HackingButtons.Num() - 1 && CurrentlyFocused < EnabledButtons)
	{
		HackingButtons[CurrentlyFocused]->SetUnFocused();
		CurrentlyFocused++;
		HackingButtons[CurrentlyFocused]->SetFocused();
		HackDescription->SetText(HackingButtons[CurrentlyFocused]->GetDescription());
	}

}

void UGUI_HackingMenu::FocusPreviousHackButton()
{
	if (CurrentlyFocused > 0)
	{
		HackingButtons[CurrentlyFocused]->SetUnFocused();
		CurrentlyFocused--;
		HackingButtons[CurrentlyFocused]->SetFocused();
		HackDescription->SetText(HackingButtons[CurrentlyFocused]->GetDescription());
	}
}

void UGUI_HackingMenu::UpdateButtonDisplay(TArray<UHackEffect*>& Hacks)
{
	for (int i = 0; i < Hacks.Num(); i++)
	{
		HackingButtons[i]->SetHack(Hacks[i]);
	}
	EnabledButtons = Hacks.Num() -1;
	HackDescriptionParent->SetVisibility(ESlateVisibility::Visible);
	HackDescription->SetText(HackingButtons[CurrentlyFocused]->GetDescription());
}

void UGUI_HackingMenu::DisableHackButtons()
{
	for (UGUB_HackingButton* Button : HackingButtons)
	{
		Button->SetVisibility(ESlateVisibility::Hidden);
	}
	HackingButtons[CurrentlyFocused]->SetUnFocused();
	EnabledButtons = 0;
	CurrentlyFocused = 0;
	HackingButtons[CurrentlyFocused]->SetFocused();
	FocusedObject = nullptr;
	HackDescriptionParent->SetVisibility(ESlateVisibility::Hidden);
}

void UGUI_HackingMenu::TriggerHack()
{
	if (!FocusedObject || IsHacking())
	{
		return;
	}
	SetHackingStarted();

}

void UGUI_HackingMenu::SetHackingStarted()
{
	bIsHacking = true;
	HackingButtons[CurrentlyFocused]->StartHack(FocusedObject);
	for (UGUB_HackingButton* Button : HackingButtons)
	{
		Button->SetDisplayDisabled();
	}
	HackingButtons[CurrentlyFocused]->SetFocused();
}

void UGUI_HackingMenu::SetHackingEnded()
{
	bIsHacking = false;
	for (UGUB_HackingButton* Button : HackingButtons)
	{
		Button->SetDisplayEnabled();
	}
	HackingButtons[CurrentlyFocused]->SetFocused();
}

void UGUI_HackingMenu::NativeConstruct()
{
	Super::NativeConstruct();


	//we do this as HackingButtons we be added the the array every time it is added to the viewport if not,
	// and we cant empty the array, as some functions need access to the buttons even when not active
	if (HackingButtons.IsEmpty())
	{
		HackingButtons.Add(HackingButton1);
		HackingButtons.Add(HackingButton2);
		HackingButtons.Add(HackingButton3);
		HackingButtons.Add(HackingButton4);
		HackingButtons.Add(HackingButton5);
	}



	for (UGUB_HackingButton* Button : HackingButtons)
	{
		Button->SetHackingMenu(this);
	}

	HackingButtons[0]->SetFocused();
	HackDescriptionParent->SetVisibility(ESlateVisibility::Hidden);

}

void UGUI_HackingMenu::NativeDestruct()
{
	Super::NativeDestruct();

	HackingButtons[CurrentlyFocused]->SetUnFocused();
	CurrentlyFocused = 0;

}


