// CodeLikeMe Menu System - (c) 2025 CodeLikeMe GmbH


#include "ExtendedUserSettingSubsystem.h"
#include "GenericPlatform/GenericApplication.h"
#include "Widgets/SWindow.h"

TArray<FDisplayInfo> UExtendedUserSettingSubsystem::GetAllFDisplayInfo() const
{
	TArray<FDisplayInfo> MonitorInfoArray;

	FDisplayMetrics DisplayMetrics;
	FDisplayMetrics::RebuildDisplayMetrics(DisplayMetrics);
	
	for(const FMonitorInfo& MonitorInfo : DisplayMetrics.MonitorInfo)
	{
		MonitorInfoArray.Add(FDisplayInfo(
			MonitorInfo.Name,
			MonitorInfo.ID,
			MonitorInfo.NativeWidth,
			MonitorInfo.NativeHeight,
			MonitorInfo.MaxResolution,
			MonitorInfo.bIsPrimary,
			MonitorInfo.DPI
		));
	}

	return MonitorInfoArray;
}


void UExtendedUserSettingSubsystem::SetActiveDisplayById(const FString& DisplayId)
{
	FDisplayMetrics DisplayMetrics;
	FDisplayMetrics::RebuildDisplayMetrics(DisplayMetrics);
	for (const FMonitorInfo& MonitorInfo : DisplayMetrics.MonitorInfo)
	{
		if (MonitorInfo.ID == DisplayId)
		{
			UE_LOG(LogTemp, Log, TEXT("Setting active display to ID: %s"), *DisplayId);

			FVector2D NewWindowPosition(MonitorInfo.WorkArea.Left, MonitorInfo.WorkArea.Top);

			if (GEngine && GEngine->GameViewport)
			{
				TSharedPtr<SWindow> GWindow = GEngine->GameViewport->GetWindow();

				if (GWindow.IsValid())
				{
					GWindow->MoveWindowTo(NewWindowPosition);
					UE_LOG(LogTemp, Log, TEXT("Moved window to position: (%f, %f)"), NewWindowPosition.X, NewWindowPosition.Y);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("GameViewport window is not valid.."));
				}
			}

			return;
		}
	}
}
