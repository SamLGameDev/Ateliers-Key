// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI_HackSelector.h"
#include "GUB_HackingButton.h"
#include "HackEffectStore.h"
#include "Hacks/HackEffect.h"
#include "Blueprint/WidgetTree.h"


void UGUI_HackSelector::FocusNextSlot()
{
	if (CurrentButtonSlot < ButtonSlots.Num() - 1)
	{
		ButtonSlots[CurrentButtonSlot]->SetUnFocused();
		CurrentButtonSlot++;
		ButtonSlots[CurrentButtonSlot]->SetFocused();
		SlotHackDescription->SetText(ButtonSlots[CurrentButtonSlot]->GetDescription());
	}
}

void UGUI_HackSelector::FocusPreviousSlot()
{
	if (CurrentButtonSlot > 0)
	{
		ButtonSlots[CurrentButtonSlot]->SetUnFocused();
		CurrentButtonSlot--;
		ButtonSlots[CurrentButtonSlot]->SetFocused();
		SlotHackDescription->SetText(ButtonSlots[CurrentButtonSlot]->GetDescription());
	}
}

void UGUI_HackSelector::NativeConstruct()
{
	Super::NativeConstruct();

	if (!AvailableHacks)
	{
		return;
	}

	for (int i = 0; i < AvailableHacks->GetRegisteredObjects().Num(); i++)
	{
		UGUB_HackingButton* hackButton = WidgetTree->ConstructWidget<UGUB_HackingButton>
			(
				UGUB_HackingButton::StaticClass(),
				FName("HackButton" + FString::FromInt(i))
			);

		AvaialableHacksDisplay->AddChild(hackButton);

		AvailableHackButtons.Add(hackButton);

		hackButton->SetHack(AvailableHacks->GetRegisteredObjects()[i]);
	}


}

void UGUI_HackSelector::FocusNextAvailableHack()
{
	if (CurrentButtonSlot < AvailableHackButtons.Num() - 1)
	{
		AvailableHackButtons[CurrentAvailableHack]->SetUnFocused();
		CurrentAvailableHack++;
		AvailableHackButtons[CurrentAvailableHack]->SetFocused();
		PotentialHackDescription->SetText(AvailableHackButtons[CurrentAvailableHack]->GetDescription());
	}
}

void UGUI_HackSelector::FocusPreviousAvailableHack()
{
	if (CurrentButtonSlot > 0)
	{
		AvailableHackButtons[CurrentAvailableHack]->SetUnFocused();
		CurrentAvailableHack--;
		AvailableHackButtons[CurrentAvailableHack]->SetFocused();
		PotentialHackDescription->SetText(AvailableHackButtons[CurrentAvailableHack]->GetDescription());
	}
}
 