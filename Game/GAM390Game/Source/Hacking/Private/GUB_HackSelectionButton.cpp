// Fill out your copyright notice in the Description page of Project Settings.


#include "GUB_HackSelectionButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Styling/SlateTypes.h"
#include "Hacks/HackEffect.h"
#include "BP_GeneralFunctions.h"
#include "Components/Border.h"

void UGUB_HackSelectionButton::SetFocused()
{
	Parent->SetBrushColor(BorderStyle);
}

void UGUB_HackSelectionButton::SetUnFocused()
{
	Clickable->SetStyle(bIsLoaded ? LoadedStyle : UnFocusedStyle);
	Parent->SetBrushColor(bIsLoaded ? BorderLoadedColor : FLinearColor::Transparent);
}

void UGUB_HackSelectionButton::SetHack(UHackEffect* Hack)
{
	SetDisplayText(Hack->DisplayText);
	SetVisibility(ESlateVisibility::Visible);
	LoadedEffect = Hack;
}

void UGUB_HackSelectionButton::ClearLoadedHack()
{
	LoadedEffect = nullptr;
	SetLoadedDisabled();
	LoadedButton = nullptr;
}

FText UGUB_HackSelectionButton::GetDescription()
{
	if (!LoadedEffect)
	{
		return FText::FromString("");
	}

	return LoadedEffect->Description;
}

void UGUB_HackSelectionButton::SetSelectedDisplayDisabled()
{
	Clickable->SetStyle(FocusedStyle);
	DisplayText->SetColorAndOpacity(TextColor);
	Parent->SetBrushColor(FLinearColor::Transparent);
}

void UGUB_HackSelectionButton::SetSelectedDisplayEnabled()
{
	Clickable->SetStyle(LoadedStyle);
	Parent->SetBrushColor(BorderLoadedColor);
	DisplayText->SetColorAndOpacity(TextLoadedColor);
}

void UGUB_HackSelectionButton::SetDisplayText(FText Text)
{
	DisplayText->SetText(Text);
}

void UGUB_HackSelectionButton::SetLoadedDisabled()
{
	SetSelectedDisplayDisabled();
	bIsLoaded = false;
}

void UGUB_HackSelectionButton::SetLoadedEnabled()
{
	SetSelectedDisplayEnabled();
	bIsLoaded = true;
}

void UGUB_HackSelectionButton::SetLoadedButton(UGUB_HackSelectionButton* Button)
{
	LoadedButton = Button;
}

FText UGUB_HackSelectionButton::GetEffectName() const
{
	return LoadedEffect->DisplayText;
}