// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageSystem.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "BossBar.generated.h"

/**
 * 
 */
UCLASS()
class GAM390GAME_API UBossBar : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateHealthBar(UDamageSystem* damageSystem);
	
protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* healthBar;
	
};
