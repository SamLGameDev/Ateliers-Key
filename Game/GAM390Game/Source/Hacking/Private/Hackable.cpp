// Fill out your copyright notice in the Description page of Project Settings.


#include "Hackable.h"
#include "GUI_HackProgress.h"

AHackable::AHackable()
{
}

AHackable::~AHackable()
{
}
void AHackable::EnableHighlight()
{
	BaseMesh->SetOverlayMaterial(HackableObejctOutline);
}
void AHackable::DisableHighlight()
{
	BaseMesh->SetOverlayMaterial(nullptr);
}

void AHackable::SetLoadingBarProgress(const float Percent)
{
	UGUI_HackProgress* ProgressBar = Cast<UGUI_HackProgress>(LoadingBar->GetWidget());
	ProgressBar->SetFill(Percent);
}

void AHackable::EnableLoadingBar()
{
	LoadingBar->SetVisibility(true);
}

void AHackable::DisableLoadingBar()
{
	LoadingBar->SetVisibility(false);
}

