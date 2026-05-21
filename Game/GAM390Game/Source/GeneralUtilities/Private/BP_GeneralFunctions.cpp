// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_GeneralFunctions.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Framework/Application/AnalogCursor.h"

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

	//Controller->SetMouseLocation(0 ,0);

	FSlateApplication& app = FSlateApplication::Get();

	float mouseX, mouseY;
	Controller->GetMousePosition(mouseX, mouseY);
	
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
	if (false)
	{
		// Get the widget window under the mouse
		TArray<TSharedRef<SWindow>> WindowsArray;
		FWidgetPath WidgetPath = app.LocateWindowUnderMouse(app.GetCursorPos(), WindowsArray);
 
		for (int32 i = WidgetPath.Widgets.Num() - 1; i >= 0; --i)
		{
			const FArrangedWidget& ArrangedWidget = WidgetPath.Widgets[i];
			const TSharedRef<SWidget>& Widget = ArrangedWidget.Widget;
			TSharedPtr<SWindow> Window = app.FindWidgetWindow(Widget);
			if (Window.IsValid())
			{
				// Found the window under the mouse
				app.ProcessMouseButtonDownEvent(Window->GetNativeWindow(), MouseEvent);
				return;
			}
		}
	}
	TSharedPtr<FGenericWindow, ESPMode::ThreadSafe> NullWindow;
	app.ProcessMouseButtonDownEvent(NullWindow, MouseEvent);
	return;

	//FInputModeUIOnly onlyUI;

	//onlyUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	//Controller->SetInputMode(onlyUI);
}
