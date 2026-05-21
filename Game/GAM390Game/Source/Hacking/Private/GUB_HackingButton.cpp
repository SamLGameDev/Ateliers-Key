// Fill out your copyright notice in the Description page of Project Settings.


#include "GUB_HackingButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Styling/SlateTypes.h"
#include "Hacks/HackEffect.h"
#include "BP_GeneralFunctions.h"
#include "Hackable.h"
#include "Components/Border.h"
#include "GUI_HackingMenu.h"

void UGUB_HackingButton::SetFocused()
{
	Parent->SetBrushColor(BorderStyle);
}

void UGUB_HackingButton::SetUnFocused()
{
	Clickable->SetStyle(CurrentUnFocusedStyle);
	Parent->SetBrushColor(CurrentBorderColor);
}

void UGUB_HackingButton::SetSelectedDisplayLoaded()
{
	Clickable->SetStyle(LoadedStyle);
	Parent->SetBrushColor(BorderLoadedColor);
	DisplayText->SetColorAndOpacity(TextLoadedColor);
	CurrentUnFocusedStyle = LoadedStyle;
	CurrentBorderColor = BorderLoadedColor;
}

void UGUB_HackingButton::SetSelectedDisplayUnLoaded()
{
	Clickable->SetStyle(UnFocusedStyle);
	Parent->SetBrushColor(FLinearColor::Transparent);
	DisplayText->SetColorAndOpacity(TextUnLoadedColor);
	CurrentUnFocusedStyle = UnFocusedStyle;
	CurrentBorderColor = FLinearColor::Transparent;
}

void UGUB_HackingButton::SetUpButton()
{
	CurrentUnFocusedStyle = UnFocusedStyle;
	CurrentBorderColor = FLinearColor::Transparent;
}

void UGUB_HackingButton::SetHack(UHackEffect* Hack)
{
	SetDisplayText(Hack->DisplayText);
	SetVisibility(ESlateVisibility::Visible);
	LoadedEffect = Hack;
}

FText UGUB_HackingButton::GetDescription()
{
	return LoadedEffect->Description;
}


void UGUB_HackingButton::SetDisplayText(FText Text)
{
	DisplayText->SetText(Text);
}
