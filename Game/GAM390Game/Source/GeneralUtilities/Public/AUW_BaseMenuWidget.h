// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AUW_BaseMenuWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GENERALUTILITIES_API UAUW_BaseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void SetPreviousMenu(UAUW_BaseMenuWidget* PreviousMenu) { m_PreviousMenu = PreviousMenu; };

	UFUNCTION(BlueprintCallable)
	virtual UAUW_BaseMenuWidget* GetPreviousMenu() { return m_PreviousMenu; }

protected:

	UPROPERTY()
	UAUW_BaseMenuWidget* m_PreviousMenu;
	
};
