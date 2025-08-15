// Fill out your copyright notice in the Description page of Project Settings.


#include "Hackable.h"
#include "Hacks/HackEffect.h"
#include "GUI_HackProgress.h"

AHackable::AHackable()
{
}

void AHackable::EnableHighlight()
{
	for (UMeshComponent* mesh : BaseMesh)
	{
		mesh->SetOverlayMaterial(HackableObejctOutline);
	}

}
void AHackable::DisableHighlight()
{
	for (UMeshComponent* mesh : BaseMesh)
	{
		mesh->SetOverlayMaterial(nullptr);
	}

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

void AHackable::StartHack(UHackEffect* Hack)
{

	FTimerDelegate HackProgress;

	HackProgress.BindUFunction(this, "ProgressHack", Hack, Hack->TimeToHack);

	GetWorld()->GetTimerManager().SetTimerForNextTick(HackProgress);

	EnableLoadingBar();

	SetLoadingBarProgress(0);
}

void AHackable::ProgressHack(UHackEffect* Hack, float TimeRemaining)
{
	TimeRemaining -= GetWorld()->GetDeltaSeconds();

	const float fillPercent = 1 - (TimeRemaining / Hack->TimeToHack);

	SetLoadingBarProgress(fillPercent);

	if (TimeRemaining <= 0)
	{
		EndHack(Hack);
		return;
	}

	FTimerDelegate HackProgress;

	HackProgress.BindUFunction(this, "ProgressHack", Hack, TimeRemaining);

	GetWorld()->GetTimerManager().SetTimerForNextTick(HackProgress);

}

void AHackable::EndHack(UHackEffect* Hack)
{
	DisableLoadingBar();
	Hack->ExecuteHack(this);
}

void AHackable::BeginDestroy()
{
	Super::BeginDestroy();
	if (HackableObjects)
	{
		HackableObjects->DeregisterObject(this);
	}

}

