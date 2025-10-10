// Fill out your copyright notice in the Description page of Project Settings.

#include "SceneManagement.h"

#include "BUIUW_MainMenu.h"

#include "BP_SceneManager.h"

void UBUIUW_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	SetUpButtons();
}

void UBUIUW_MainMenu::Play() const
{
	UBP_SceneManager::LoadLevel("Level1Base", GetWorld());
}

void UBUIUW_MainMenu::SetUpButtons()
{
	PlayButton->OnClicked.AddDynamic(this, &UBUIUW_MainMenu::OnPlayClicked);
}

void UBUIUW_MainMenu::OnPlayClicked() 
{
	Play();
}
