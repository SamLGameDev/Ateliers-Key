// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_UserWidgetFunctions.h"
#include "AUW_BaseMenuWidget.h"
#include "InputMappingContext.h"

void UBP_UserWidgetFunctions::ChangeWidget(UAUW_BaseMenuWidget* Current, UAUW_BaseMenuWidget* NewWidget)
{
	Current->SetVisibility(ESlateVisibility::Hidden);

	NewWidget->SetPreviousMenu(Current);

	NewWidget->SetVisibility(ESlateVisibility::Visible);
}


