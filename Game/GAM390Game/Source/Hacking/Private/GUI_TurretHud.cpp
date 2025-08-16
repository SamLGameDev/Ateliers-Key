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
            RemainingTime = 0.0f;

        int32 s = FMath::FloorToInt(RemainingTime);
        int32 ms = FMath::FloorToInt((RemainingTime - s) * 1000);

        int32 firstDigitMs = ms / 100;

        FString CountdownString = FString::Printf(TEXT("%d.%d"), s, firstDigitMs);

        UpdateCountdownText(CountdownString);
    }
}

void UGUI_TurretHud::UpdateBulletCount(int currentBulletCount, int maxBulletCount)
{
    currentBulletCountText->SetText(FText::AsNumber(currentBulletCount));
    maxBulletCountText->SetText(FText::AsNumber(maxBulletCount));
}
