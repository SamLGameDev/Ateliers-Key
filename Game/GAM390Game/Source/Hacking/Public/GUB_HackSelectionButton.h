// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GUB_HackSelectionButton.generated.h"


class UButton;
class UTextBlock;
struct FButtonStyle;
class UHackEffect;
class UBorder;

/**
 * 
 */
UCLASS()
class HACKING_API UGUB_HackSelectionButton : public UUserWidget
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

	void ClearLoadedHack();

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

	FText GetDescription();

	void SetSelectedDisplayDisabled();

	void SetSelectedDisplayEnabled();

	void SetDisplayText(FText Text);

	void SetLoadedDisabled();

	void SetLoadedEnabled();

	bool IsLoaded()
	{
		return bIsLoaded;
	}

	void SetLoadedButton(UGUB_HackSelectionButton* Button);

	UGUB_HackSelectionButton* GetLoadedButton()
	{
		return LoadedButton;
	}

	const bool IsEmpty() const
	{
		if (LoadedEffect)
		{
			return false;
		}
		return true;
	}

	UFUNCTION(BlueprintCallable)
	FText GetEffectName() const;

private:
	UHackEffect* LoadedEffect;

	UPROPERTY(EditAnywhere)
	FButtonStyle LoadedStyle;

	UPROPERTY(EditAnywhere)
	FLinearColor BorderLoadedColor;

	UPROPERTY(EditAnywhere)
	FSlateColor TextLoadedColor;

	UGUB_HackSelectionButton* LoadedButton;

	UPROPERTY(EditAnywhere)
	FSlateColor TextColor;

	bool bIsLoaded;
};
