// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_GeneralFunctions.h"

UBP_GeneralFunctions::FInterfaceSignature UBP_GeneralFunctions::InterfaceDelegate;

void UBP_GeneralFunctions::SetToGameplayControls(APlayerController* Controller)
{
	Controller->bShowMouseCursor = false;

	const FInputModeGameOnly GameOnly;

	Controller->SetInputMode(GameOnly);
}

void UBP_GeneralFunctions::SetToMenuControls(APlayerController* Controller)
{
	Controller->bShowMouseCursor = true;

	FInputModeUIOnly onlyUI;

	onlyUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	Controller->SetInputMode(onlyUI);
}
