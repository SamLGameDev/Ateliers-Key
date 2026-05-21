// Fill out your copyright notice in the Description page of Project Settings.


#include "BUIUW_MainMenu.h"
#include "SceneManagement.h"
#include "BP_GeneralFunctions.h"
#include "BP_SceneManager.h"
#include "BP_UserWidgetFunctions.h"
#include "BUIUW_Options.h"

void UBUIUW_MainMenu::CreateConnectingWidgets()
{
	OptionsMenu = CreateWidget<UBUIUW_Options>(this, OptionsClass, "OptionsMenu");
	OptionsMenu->SetVisibility(ESlateVisibility::Hidden);
	OptionsMenu->AddToViewport();
}

void UBUIUW_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	CreateConnectingWidgets();
	
	SetUpButtons();

	PlayButton->SetFocus();

	UBP_GeneralFunctions::SetToMenuControls(GetWorld()->GetFirstPlayerController());
}

void UBUIUW_MainMenu::Play() const
{
	UBP_SceneManager::LoadLevel("Level1Base", GetWorld());
}

void UBUIUW_MainMenu::Quit() const
{
	UBP_SceneManager::Quit(GetWorld());
}

void UBUIUW_MainMenu::SetUpButtons()
{
	PlayButton->OnClicked.AddDynamic(this, &UBUIUW_MainMenu::OnPlayClicked);
	OptionsButton->OnClicked.AddDynamic(this, &UBUIUW_MainMenu::OnOptionsClicked);
	QuitButton->OnClicked.AddDynamic(this, &UBUIUW_MainMenu::OnQuitClicked);
}

void UBUIUW_MainMenu::OnPlayClicked() 
{
	Play();
}

void UBUIUW_MainMenu::OnOptionsClicked()
{
	UBP_UserWidgetFunctions::ChangeWidget(this, OptionsMenu);
}

void UBUIUW_MainMenu::OnQuitClicked()
{
	Quit();
}
