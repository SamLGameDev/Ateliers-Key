// Fill out your copyright notice in the Description page of Project Settings.


#include "VirtualCursorActionRouter.h"

#include "CommonInputSubsystem.h"
#include "CommonUI/Private/Input/UIActionRouterTypes.h"

void FVirtualCursor::Initialize()
{
	FCommonAnalogCursor::Initialize();
	bIsAnalogMovementEnabled = true;
	Mode = AnalogCursorMode::Direct;
}

FVirtualCursor::FVirtualCursor(const UCommonUIActionRouterBase& InActionRouter) : FCommonAnalogCursor(InActionRouter){}

TSharedRef<FCommonAnalogCursor> UVirtualCursorActionRouter::MakeAnalogCursor() const
{
	return FVirtualCursor::CreateAnalogCursor<FVirtualCursor>(*this);
}

void UVirtualCursorActionRouter::AddScrollable(UWidget* widget)
{
	RegisterScrollRecipient(*widget);
}



