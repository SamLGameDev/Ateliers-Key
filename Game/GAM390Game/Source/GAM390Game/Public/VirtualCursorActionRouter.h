 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Input/CommonAnalogCursor.h"
#include "Input/CommonUIActionRouterBase.h"
#include "VirtualCursorActionRouter.generated.h"


class FVirtualCursor : public FCommonAnalogCursor
{
public:
	virtual void Initialize() override; 
	FVirtualCursor(const UCommonUIActionRouterBase& InActionRouter);
	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override;
private:
};

/**
 * 
 */
UCLASS()
class GAM390GAME_API UVirtualCursorActionRouter : public UCommonUIActionRouterBase
{
	GENERATED_BODY()

protected:
	virtual TSharedRef<FCommonAnalogCursor> MakeAnalogCursor() const override;
};
