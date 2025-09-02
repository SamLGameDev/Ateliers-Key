// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI_TurretHud.h"
#include "HackableTurret.h"
#include "Components/TextBlock.h"

void UGUI_TurretHud::NativeConstruct()
{
    Super::NativeConstruct();

    RemainingTime = CountdownTime;
}

void UGUI_TurretHud::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (RemainingTime > 0.0f)
    {
        RemainingTime -= InDeltaTime;

        if (RemainingTime < 0.0f)
        {
            RemainingTime = 0.0f;
        }

        const FString CountdownString = FString::Printf(TEXT("%0.1f"), RemainingTime);

        UpdateCountdownText(CountdownString);
    }
}

void UGUI_TurretHud::UpdateBulletCount(const int currentBulletCount, const int maxBulletCount)
{
    currentBulletCountText->SetText(FText::AsNumber(currentBulletCount));
    maxBulletCountText->SetText(FText::AsNumber(maxBulletCount));
}
