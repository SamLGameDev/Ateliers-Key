// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI_HackProgress.h"
#include "Components/ProgressBar.h"

void UGUI_HackProgress::SetFill(float InPercent)
{
	LoadingBar->SetPercent(InPercent);
}