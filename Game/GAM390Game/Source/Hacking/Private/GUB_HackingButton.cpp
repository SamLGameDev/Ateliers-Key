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
	Parent->SetBrushColor(HackingMenu->IsHacking() ? BorderDisabledColor : BorderStyle);
}

void UGUB_HackingButton::SetUnFocused()
{
	Clickable->SetStyle(HackingMenu->IsHacking() ? DisabledStyle: UnFocusedStyle);
	Parent->SetBrushColor(FLinearColor::Transparent);
}

void UGUB_HackingButton::SetHack(UHackEffect* Hack)
{
	SetDisplayText(Hack->DisplayText);
	SetVisibility(ESlateVisibility::Visible);
	LoadedEffect = Hack;
}

void UGUB_HackingButton::StartHack(UObject* HackedObject)
{
	AHackable* Object = Cast<AHackable>(HackedObject);

	Object->EnableLoadingBar();

	FTimerDelegate HackDel;


	HackDel.BindUFunction(this, "ProgressHack", Object, LoadedEffect->TimeToHack);

	GetWorld()->GetTimerManager().SetTimerForNextTick(HackDel);
}

FText UGUB_HackingButton::GetDescription()
{
	return LoadedEffect->Description;
}

void UGUB_HackingButton::SetDisplayDisabled()
{
	Clickable->SetStyle(DisabledStyle);
	DisplayText->SetColorAndOpacity(TextDisabledColor);
}

void UGUB_HackingButton::SetDisplayEnabled()
{
	Clickable->SetStyle(FocusedStyle);
	DisplayText->SetColorAndOpacity(TextColor);
}

void UGUB_HackingButton::SetDisplayText(FText Text)
{
	DisplayText->SetText(Text);
}

void UGUB_HackingButton::ProgressHack(AHackable* HackedObject, float TimeRemaining)
{
	TimeRemaining -= GetWorld()->GetDeltaSeconds();

	const float fillPercent = 1 - (TimeRemaining / LoadedEffect->TimeToHack);

	HackedObject->SetLoadingBarProgress(fillPercent);

	if (TimeRemaining <= 0)
	{
		TriggerHack(HackedObject);
	}
	else
	{
		FTimerDelegate HackDel;

		HackDel.BindUFunction(this, "ProgressHack", HackedObject, TimeRemaining);

		GetWorld()->GetTimerManager().SetTimerForNextTick(HackDel);
	}

}

void UGUB_HackingButton::TriggerHack(AHackable* HackedObject)
{
	HackingMenu->SetHackingEnded();
	HackedObject->DisableLoadingBar();
	LoadedEffect->ExecuteHack(HackedObject);
}
