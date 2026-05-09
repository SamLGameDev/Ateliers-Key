 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Input/CommonAnalogCursor.h"
#include "Input/CommonUIActionRouterBase.h"
#include "VirtualCursorActionRouter.generated.h"



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
class FVirtualCursor : public FCommonAnalogCursor
{
public:

	template <typename AnalogCursorT = FVirtualCursor>
	static TSharedRef<AnalogCursorT> CreateAnalogCursor(const UVirtualCursorActionRouter& InActionRouter)
	{
		TSharedRef<AnalogCursorT> NewCursor = MakeShareable(new AnalogCursorT(InActionRouter));
		NewCursor->Initialize();
		return NewCursor;
	}
protected:
	
	virtual void Initialize() override; 
	FVirtualCursor(const UCommonUIActionRouterBase& InActionRouter);
	//virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override;

//	FVector2D LastCursorPosition;
};