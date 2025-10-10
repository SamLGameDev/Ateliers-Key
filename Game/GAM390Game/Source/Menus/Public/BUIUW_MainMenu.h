// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AUW_BaseMenuWidget.h"
#include "Components/Button.h"
#include "BUIUW_MainMenu.generated.h"

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
	
	void NativeConstruct() override;

	void Play() const;
	
	void SetUpButtons();

	UFUNCTION()
	void OnPlayClicked();

	

	
};
