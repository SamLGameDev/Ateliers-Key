// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "uInt8Store.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "GUI_HackSelector.generated.h"

class UGUB_HackSelectionButton;
class UHackEffectStore;

/**
 * 
 */
UCLASS()
class HACKING_API UGUI_HackSelector : public UUserWidget
{
	GENERATED_BODY()

public:
	float GetRotationAmount(const UImage* LastBullet);
	
	void MoveToNextBullet(const int8 RotDir);
	bool CanRotateChamber() const;

	UFUNCTION()
	void FocusNextSlot();
	void StartChamberRotation(int8 RotDir);

	UFUNCTION()
	void FocusPreviousSlot();

	UFUNCTION()
	void EndChamberRotation();


	UFUNCTION()
	void FocusNextAvailableHack();

	UFUNCTION()
	void FocusPreviousAvailableHack();


	UFUNCTION()
	void LoadSelectedToSlot();

	void ReduceBulletsIfNeeded(const UGUB_HackSelectionButton* loadedButton) const;

	void ReduceRemainingBullets() const;

	void UpdateRemainingBullets() const;


	UFUNCTION()
	void Exit();

	UPROPERTY(BlueprintReadWrite)
	UWidgetAnimation* FocusNextHackAnim;

private:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UScrollBox* AvaialableHacksDisplay;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGUB_HackSelectionButton* HackingButton1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGUB_HackSelectionButton* HackingButton2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGUB_HackSelectionButton* HackingButton3;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGUB_HackSelectionButton* HackingButton4;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGUB_HackSelectionButton* HackingButton5;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGUB_HackSelectionButton* HackingButton6;

	TArray<UGUB_HackSelectionButton*> ButtonSlots;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGUB_HackSelectionButton> BPHackingButton;

	int CurrentButtonSlot = 0;


	TArray<UGUB_HackSelectionButton*> AvailableHackButtons;

	virtual void NativeConstruct() override;
	void RotateAllBulletsAroundCenter(int8 RotDir, float Amount);
	void SetSelectedSprite();
	void PrepareCurrentBulletForSelection();
	void SetCurrentBulletToSelected(int8 RotDir);

	UPROPERTY(EditDefaultsOnly)
	UHackEffectStore* AvailableHacks;

	int CurrentAvailableHack;


	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* SlotHackDescription;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* PotentialHackDescription;

	UPROPERTY(EditAnywhere)
	UuInt8Store* UnlockedHackSlots;

	UPROPERTY(EditDefaultsOnly)
	UHackEffectStore* LoadedHacks;

	UPROPERTY(EditDefaultsOnly)
	UuInt8Store* CurrentHackBullets;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* CurrentBulletsDisplay;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* ChamberParent;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ChamberBullet1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ChamberBullet2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ChamberBullet3;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ChamberBullet4;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ChamberBullet5;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ChamberBullet6;

	TArray<UImage*> ChamberBullets;

	FTimerHandle MovingChamberHandle;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* SelectedUnFilled;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* SelectedFilled;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* UnFilled;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* Filled;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* Locked;
	
	float LatestRotationGoal = 0;

	float CurrentRotAmount = 0;

	FVector2D OriginalPos;

	FVector2D LastPos;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UImage* SelectedSlotLocation;

	UFUNCTION()
	void RotateToLatestChamberPos();

	void RotateBulletAroundCenter(const UImage* bullet, int8 RotDir, float Amount) const;
	bool LerpImageToPosition(const UImage* ToMove, const UImage* Target) const;
	bool LerpImageToPosition(const UImage* ToMove, const FVector2D Target) const;
	bool LerpImageToScale(UImage* ToMove, FVector2D Scale) const;
	void LerpImageToColor(float Alpha, UImage* ToMove, FLinearColor FromColor, FLinearColor ToColor) const;

	UFUNCTION()
	void MoveToSelectedPositon(float Alpha);

	void SetBulletToSelectedInstant();
	void SetUnselectedSprite();

	UFUNCTION()
	void MoveToUnselectedPosition(float Alpha, int8 RotDir);

	UPROPERTY(EditDefaultsOnly)
	FSlateColor BeforeSelectedLerpColor;

	UPROPERTY(EditDefaultsOnly)
	float ColorBlendSpeed;

	UPROPERTY(EditDefaultsOnly)
	float ChamberRotationSpeed;

	FVector2D UnselectedPos;


	UPROPERTY(EditDefaultsOnly)
	UTextBlock* MiddleText;

	UPROPERTY(EditDefaultsOnly)
	UTextBlock* TopText;

	UPROPERTY(EditDefaultsOnly)
	UTextBlock* BottomText;

	UPROPERTY(EditDefaultsOnly)
	UTextBlock* MiddleStationaryText;

	bool bEndChamberRotation;
};
