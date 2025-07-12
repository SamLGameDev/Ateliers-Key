// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GUB_HackingButton.generated.h"

class UButton;
class UTextBlock;
struct FButtonStyle;
class UHackEffect;
class AHackable;
class UBorder;
class UGUI_HackingMenu;

/**
 * 
 */
UCLASS()
class HACKING_API UGUB_HackingButton : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget), BlueprintReadWrite)
	UBorder* Parent;

	UPROPERTY(EditAnywhere, meta = (BindWidget), BlueprintReadWrite)
	UButton* Clickable;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* DisplayText;

	void SetFocused();

	void SetUnFocused();

	void SetHack(UHackEffect* Hack);

	UHackEffect* const GetHack() const
	{
		return LoadedEffect;
	}

	UPROPERTY(EditAnywhere)
	FButtonStyle FocusedStyle;

	UPROPERTY(EditAnywhere)
	FLinearColor BorderStyle;

	UPROPERTY(EditAnywhere)
	FButtonStyle UnFocusedStyle;

	void StartHack(UObject* HackedObject);

	FText GetDescription();

	void SetHackingMenu(UGUI_HackingMenu* Menu)
	{
		HackingMenu = Menu;
	}

	void SetDisplayDisabled();

	void SetDisplayEnabled();

	void SetDisplayText(FText Text);



private:
	UHackEffect* LoadedEffect;

	UGUI_HackingMenu* HackingMenu;

	UPROPERTY(EditAnywhere)
	FButtonStyle DisabledStyle;

	UPROPERTY(EditAnywhere)
	FLinearColor BorderDisabledColor;

	UPROPERTY(EditAnywhere)
	FSlateColor TextDisabledColor;


	UPROPERTY(EditAnywhere)
	FSlateColor TextColor;


	UFUNCTION()
	void ProgressHack(AHackable* HackedObject, float TimeRemaining);

	UFUNCTION()
	void TriggerHack(AHackable* HackedObject);
};
