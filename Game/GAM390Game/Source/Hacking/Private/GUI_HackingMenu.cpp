// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI_HackingMenu.h"
#include "Components/ScrollBox.h"
#include "GUB_HackingButton.h"
#include "Hacks/HackEffect.h"
#include "Components/TextBlock.h"
#include "HackEffectVariable.h"
#include "HackEffectStore.h"
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

void UGUI_HackingMenu::UpdateButtonDisplay(const TArray<UHackEffect*>& Hacks)
{
	if (Hacks.IsEmpty())
	{
		for (UGUB_HackingButton* Button : HackingButtons)
		{
			Button->SetVisibility(ESlateVisibility::Hidden);
		}
		return;
	}

	for (int i = 0; i < HackingButtons.Num(); i++)
	{
		if (Hacks.IsValidIndex(i))
		{
			HackingButtons[i]->SetHack(Hacks[i]);
			HackingButtons[i]->SetVisibility(ESlateVisibility::Visible);
			continue;
		}
		HackingButtons[i]->SetVisibility(ESlateVisibility::Hidden);
	}
	EnabledButtons = Hacks.Num() - 1;
	HackDescriptionParent->SetVisibility(ESlateVisibility::Visible);
	HackDescription->SetText(HackingButtons[CurrentlyFocused]->GetDescription());
}


void UGUI_HackingMenu::TriggerHack()
{
	SetLoadedHack();
}

void UGUI_HackingMenu::SetLoadedHack()
{
	LoadedHack->SetObject(HackingButtons[CurrentlyFocused]->GetHack());
	HackingButtons[CurrentlyFocused]->SetFocused();

	for (UGUB_HackingButton* Button : HackingButtons)
	{
		Button->SetSelectedDisplayUnLoaded();
	}

	HackingButtons[CurrentlyFocused]->SetSelectedDisplayLoaded();
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
		for (UGUB_HackingButton* Button : HackingButtons)
		{
			Button->SetUpButton();
		}
	}


	for (UGUB_HackingButton* Button : HackingButtons)
	{
		Button->SetHackingMenu(this);
	}

	HackingButtons[0]->SetFocused();
	HackDescriptionParent->SetVisibility(ESlateVisibility::Hidden);

	UpdateButtonDisplay(LoadedHacks->GetRegisteredObjects());
}

void UGUI_HackingMenu::NativeDestruct()
{
	Super::NativeDestruct();

	HackingButtons[CurrentlyFocused]->SetUnFocused();
	CurrentlyFocused = 0;
}
