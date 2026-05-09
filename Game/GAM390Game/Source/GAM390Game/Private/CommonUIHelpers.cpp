// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonUIHelpers.h"

#include "CommonInputSubsystem.h"

void UCommonUIHelpers::SimulateUIMouseClick(UObject* WorldContextObject)
{
	FSlateApplication& app = FSlateApplication::Get();

	float mouseX, mouseY;
	WorldContextObject->GetWorld()->GetFirstPlayerController()->GetMousePosition(mouseX, mouseY);
	
	FPointerEvent MouseEvent(
		0,
		app.CursorPointerIndex,
		app.GetCursorPos(),
		app.GetLastCursorPos(),
		app.GetPressedMouseButtons(),
		EKeys::LeftMouseButton,
		0,
		app.GetPlatformApplication()->GetModifierKeys()
	);
	TSharedPtr<FGenericWindow, ESPMode::ThreadSafe> NullWindow;
	app.ProcessMouseButtonDownEvent(NullWindow, MouseEvent);

	app.ProcessMouseButtonUpEvent(MouseEvent);
}
