// Copyright Epic Games, Inc. All Rights Reserved.

#include "CLM_DisplayLibraryBPLibrary.h"
#include "CLM_DisplayLibraryBPLibrary.h"
#include "GenericPlatform/GenericApplication.h"
#include "Engine.h"
#include "Widgets/SWindow.h"

UCLM_DisplayLibraryBPLibrary::UCLM_DisplayLibraryBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

int UCLM_DisplayLibraryBPLibrary::GetDisplayCount()
{
	FDisplayMetrics Displays;
	FDisplayMetrics::RebuildDisplayMetrics(Displays);

	return Displays.MonitorInfo.Num();
}

TArray<FDisplayInfo> UCLM_DisplayLibraryBPLibrary::GetAllDisplays()
{
	TArray<FDisplayInfo> AllDisplays;

	FDisplayMetrics Displays;
	FDisplayMetrics::RebuildDisplayMetrics(Displays);

	for (const FMonitorInfo& Monitor : Displays.MonitorInfo)
	{
		AllDisplays.Add(FDisplayInfo(Monitor.Name, Monitor.ID, Monitor.NativeWidth, Monitor.NativeHeight, Monitor.MaxResolution, Monitor.bIsPrimary, Monitor.DPI));
	}

	return AllDisplays;
}

bool UCLM_DisplayLibraryBPLibrary::SetActiveDisplay(int32 DisplayIndex)
{
	FDisplayMetrics Displays;
	FDisplayMetrics::RebuildDisplayMetrics(Displays);
	
	if (DisplayIndex > Displays.MonitorInfo.Num())
	{
		// Non existing display
		return false;
	}

	const FMonitorInfo TargetMonitor = Displays.MonitorInfo[DisplayIndex];
	//TargetMonitor.WorkArea.
	FVector2D WindowPosition(static_cast<float>(TargetMonitor.WorkArea.Left), static_cast<float>(TargetMonitor.WorkArea.Top));

	if (GEngine && GEngine->GameViewport)
	{
		// Display switching
		TSharedPtr<SWindow> GWindow = GEngine->GameViewport->GetWindow();
		GWindow->MoveWindowTo(WindowPosition);		

		//Setting resolution
		UGameUserSettings* UserSettings = GEngine->GameUserSettings;
		UserSettings->SetScreenResolution(FIntPoint(TargetMonitor.NativeWidth, TargetMonitor.NativeHeight));
		UserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
		UserSettings->ApplySettings(true);
		UserSettings->ApplyResolutionSettings(false);

	}





	return true;
}
