// Fill out your copyright notice in the Description page of Project Settings.


#include "VirtualCursorActionRouter.h"

#include "CommonInputSubsystem.h"

void FVirtualCursor::Initialize()
{
	FCommonAnalogCursor::Initialize();
	bIsAnalogMovementEnabled = true;
}

FVirtualCursor::FVirtualCursor(const UCommonUIActionRouterBase& InActionRouter) : FCommonAnalogCursor(InActionRouter)
{
}

void FVirtualCursor::Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor)
{
	FCommonAnalogCursor::Tick(DeltaTime, SlateApp, Cursor);
	const TSharedRef<FSlateUser> SlateUser = SlateApp.GetUser(GetOwnerUserIndex()).ToSharedRef();
	const FVector2D NewPosition = CalculateTickedCursorPosition(DeltaTime, SlateApp, SlateUser);

	UCommonInputSubsystem& InputSubsystem = ActionRouter.GetInputSubsystem();
	InputSubsystem.SetCursorPosition(NewPosition, true);
	GEngine->AddOnScreenDebugMessage(-1, 0.001, FColor::Green, GetAnalogValues(EAnalogStick::Left).ToString());
}

TSharedRef<FCommonAnalogCursor> UVirtualCursorActionRouter::MakeAnalogCursor() const
{
	return FVirtualCursor::CreateAnalogCursor<FVirtualCursor>(*this);
}
