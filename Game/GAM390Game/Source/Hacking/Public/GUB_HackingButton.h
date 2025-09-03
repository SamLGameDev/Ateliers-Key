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
	FLinearColor BorderStyle;

	UPROPERTY(EditAnywhere)
	FButtonStyle UnFocusedStyle;

	FText GetDescription();

	void SetHackingMenu(UGUI_HackingMenu* Menu)
	{
		HackingMenu = Menu;
	}

	void SetDisplayText(FText Text);

	void SetSelectedDisplayLoaded();

	void SetSelectedDisplayUnLoaded();

	void SetUpButton();

private:
	FButtonStyle CurrentUnFocusedStyle = UnFocusedStyle;

	FLinearColor CurrentBorderColor;

	UPROPERTY(EditAnywhere)
	FButtonStyle LoadedStyle;

	UPROPERTY(EditAnywhere)
	FLinearColor BorderLoadedColor;

	UPROPERTY(EditAnywhere)
	FSlateColor TextLoadedColor;

	UPROPERTY(EditAnywhere)
	FLinearColor BorderUnLoadedColor;

	UPROPERTY(EditAnywhere)
	FSlateColor TextUnLoadedColor;

	UHackEffect* LoadedEffect;

	UGUI_HackingMenu* HackingMenu;

	UPROPERTY(EditAnywhere)
	FSlateColor TextColor;
};
