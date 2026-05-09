// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonUIHelpers.h"

#include "CommonInputSubsystem.h"

void UCommonUIHelpers::SetCursorPosition(const FVector2D& Positon, UObject* WorldContextObject)
{
	APlayerController* controller = WorldContextObject->GetWorld()->GetFirstPlayerController();
	UCommonInputSubsystem* subsystem = ULocalPlayer::GetSubsystem<UCommonInputSubsystem>(controller->GetLocalPlayer());
	subsystem->SetCursorPosition(Positon, false);
}

FVector2D UCommonUIHelpers::GetCursorPosition(UObject* WorldContextObject)
{
	return FSlateApplication::Get().GetCursorPos();
}
