// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AUW_BaseMenuWidget.h"
#include "Components/Button.h"
#include "BUIUW_MainMenu.generated.h"

class UBUIUW_Options;

/**
 * 
 */
UCLASS()
class MENUS_API UBUIUW_MainMenu : public UAUW_BaseMenuWidget
{
	GENERATED_BODY()

public:

	
protected:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* PlayButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* OptionsButton;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBUIUW_Options> OptionsClass;

	UPROPERTY()
	UBUIUW_Options* OptionsMenu;

	void CreateConnectingWidgets();
	void NativeConstruct() override;

	void Play() const;

	void Quit() const;
	
	void SetUpButtons();

	UFUNCTION()
	void OnPlayClicked();
	
	UFUNCTION()
	void OnOptionsClicked();
	
	UFUNCTION()
	void OnQuitClicked();
	
	

	

	
};
