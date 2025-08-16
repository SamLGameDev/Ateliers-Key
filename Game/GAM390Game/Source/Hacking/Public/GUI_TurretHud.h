// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GUI_TurretHud.generated.h"

/**
 * 
 */

class UTextBlock;
class AHackableTurret;


UCLASS()
class HACKING_API UGUI_TurretHud : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    class UTextBlock* maxBulletCountText;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    class UTextBlock* currentBulletCountText;

    void UpdateBulletCount(int currentBulletCount, int maxBulletCount);

    AHackableTurret* turret;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Countdown")
    float CountdownTime = 5.0f;

    float RemainingTime;

    UFUNCTION(BlueprintImplementableEvent, Category = "Countdown")
    void UpdateCountdownText(const FString& Text);
};
