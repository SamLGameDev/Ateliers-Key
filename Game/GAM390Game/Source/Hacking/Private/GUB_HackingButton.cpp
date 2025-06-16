// Fill out your copyright notice in the Description page of Project Settings.


#include "GUB_HackingButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Styling/SlateTypes.h"
#include "Hacks/HackEffect.h"
#include "BP_GeneralFunctions.h"
#include "HackableActor.h"
#include "Components/Border.h"

void UGUB_HackingButton::SetFocused()
{
	Parent->SetBrushColor(BorderStyle);
}

void UGUB_HackingButton::SetUnFocused()
{
	Clickable->SetStyle(UnFocusedStyle);
	Parent->SetBrushColor(FLinearColor::Transparent);
}

void UGUB_HackingButton::SetHack(UHackEffect* Hack)
{
	DisplayText->SetText(Hack->DisplayText);
	SetVisibility(ESlateVisibility::Visible);
	LoadedEffect = Hack;
}

void UGUB_HackingButton::StartHack(UObject* HackedObject)
{
	AHackableActor* Object = Cast<AHackableActor>(HackedObject);

	Object->EnableLoadingBar();

	FTimerDelegate HackDel;


	HackDel.BindUFunction(this, "ProgressHack", Object, LoadedEffect->TimeToHack);

	GetWorld()->GetTimerManager().SetTimerForNextTick(HackDel);
}

FText UGUB_HackingButton::GetDescription()
{
	return LoadedEffect->Description;
}

void UGUB_HackingButton::ProgressHack(AHackableActor* HackedObject, float TimeRemaining)
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

void UGUB_HackingButton::TriggerHack(AHackableActor* HackedObject)
{
	HackedObject->DisableLoadingBar();
	LoadedEffect->ExecuteHack(HackedObject);
}
