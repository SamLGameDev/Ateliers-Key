// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GUI_HackingMenu.generated.h"

class UScrollBox;

/**
 * 
 */
UCLASS()
class HACKING_API UGUI_HackingMenu : public UUserWidget
{
	GENERATED_BODY()

private:
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UScrollBox* AvailableHacksDisplay;

	virtual void NativeConstruct() override;



};
