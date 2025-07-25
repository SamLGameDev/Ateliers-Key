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

	UFUNCTION()
	void FocusNextSlot();

	UFUNCTION()
	void FocusPreviousSlot();


	UFUNCTION()
	void FocusNextAvailableHack();

	UFUNCTION()
	void FocusPreviousAvailableHack();


	UFUNCTION()
	void LoadSelectedToSlot();

	void ReduceBulletsIfNeeded(UGUB_HackSelectionButton* loadedButton);

	void ReduceRemainngBullets();

	void UpdateRemainingBullets();


	UFUNCTION()
	void Exit();

private:

	UPROPERTY(EditAnywhere,meta=(BindWidget))
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

	int QuedInputs = 0;


	float LatestRotationGoal = 0;

	float CurrentRotAmount = 0;

	FVector2D OriginalPos;

	FVector2D LastPos;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UImage* SelectedSlotLocation;

	UFUNCTION()
	void RotateToLatestChamberPos();

	void GetRotationAroundCenter(UImage* bullet, int RotDir, float Amount);

	UFUNCTION()
	void MoveToSelectedPositon(float Alpha);

	UPROPERTY(EditDefaultsOnly)
	FSlateColor BeforeSelectedLerpColor;

	UPROPERTY(EditDefaultsOnly)
	float ColorBlendSpeed;

	UPROPERTY(EditDefaultsOnly)
	float ChamberRotationSpeed;


	
};
