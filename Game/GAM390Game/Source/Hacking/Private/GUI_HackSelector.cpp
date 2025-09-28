// Fill out your copyright notice in the Description page of Project Settings.

#include "GUI_HackSelector.h"

#include "AssetDefinitionAssetInfo.h"
#include "GUB_HackSelectionButton.h"
#include "HackEffectStore.h"
#include "Hacks/HackEffect.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ScrollBoxSlot.h"

float UGUI_HackSelector::GetRotationAmount(const UImage* LastBullet)
{
	const UImage* CurrentBullet = ChamberBullets[CurrentButtonSlot];

	const UCanvasPanelSlot* CurrentSlot = Cast<UCanvasPanelSlot>(CurrentBullet->Slot);

	const UCanvasPanelSlot* ParentSlot = Cast<UCanvasPanelSlot>(ChamberParent->Slot);

	const FVector2D CurrentPos = CurrentSlot->GetPosition();

	const FVector2D target = Cast<UCanvasPanelSlot>(LastBullet->Slot)->GetPosition();

	const FVector2D center = (ParentSlot->GetSize() / 2) - (CurrentSlot->GetSize() / 2);

	const FVector2D dirToCenterFromCurrent = CurrentPos - center;

	const FVector2D dirToCenterFromTarget = target - center;

	const float angleRad = FMath::Atan2(dirToCenterFromTarget.Y, dirToCenterFromTarget.X) - FMath::Atan2(
		dirToCenterFromCurrent.Y, dirToCenterFromCurrent.X);

	const float angleDeg = FMath::RadiansToDegrees(angleRad);

	return angleDeg;
}

void UGUI_HackSelector::MoveToNextBullet(const int8 RotDir)
{
	ButtonSlots[CurrentButtonSlot]->SetUnFocused();

	const UImage* LastBullet = ChamberBullets[CurrentButtonSlot];
	
	CurrentButtonSlot = FMath::WrapExclusive<uint8>(CurrentButtonSlot + RotDir, 0, UnlockedHackSlots->GetRegisteredObject());
	
	ButtonSlots[CurrentButtonSlot]->SetFocused();
	SlotHackDescription->SetText(ButtonSlots[CurrentButtonSlot]->GetDescription());

	float angleDeg = GetRotationAmount(LastBullet);

	//Times by ROtDir as we only need to do this if angledeg is negative for direction -1, or positive for dir 1.
	// So if we times by RotDir we get negative if anglde deg is negative for dir 1, and positive for angledeg -1
	// 1 * 1 = 1;  -1 * -1 = 1;
	if (angleDeg * RotDir > 0)
	{
		//Same princible, then -360 + angle = some amount to rotate less than 360; same for the other way round
		// 360 + angle, now angle is negative, so same result;
		angleDeg = RotDir * -360 + angleDeg;
	}

	LatestRotationGoal += angleDeg;
}

bool UGUI_HackSelector::CanRotateChamber() const
{
	if (GetWorld()->GetTimerManager().IsTimerActive(MovingChamberHandle)) return false; 
	
	if (UnlockedHackSlots->GetRegisteredObject() <= 1) return false;
	return true;
}

void UGUI_HackSelector::FocusNextSlot()
{
	StartChamberRotation(1);
}

void UGUI_HackSelector::StartChamberRotation(const int8 RotDir)
{
	if (!CanRotateChamber()) return;
	
	bEndChamberRotation = false;
	
	FTimerDelegate MovingChamberDel;
	MovingChamberDel.BindUFunction(this, "MoveToUnselectedPosition", 0, RotDir);

	MovingChamberHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(MovingChamberDel);
}

void UGUI_HackSelector::FocusPreviousSlot()
{
	StartChamberRotation(-1);
}

void UGUI_HackSelector::EndChamberRotation()
{
	bEndChamberRotation = true;
}

void UGUI_HackSelector::FocusNextAvailableHack()
{
	if (CurrentAvailableHack < AvailableHackButtons.Num() - 1 && !IsPlayingAnimation())
	{
		PlayAnimation(FocusNextHackAnim, 0, 1, EUMGSequencePlayMode::Forward, 1, true);
			

		AvailableHackButtons[CurrentAvailableHack]->SetUnFocused();
		CurrentAvailableHack++;

		if (AvailableHackButtons.IsValidIndex(CurrentAvailableHack + 1))
		{
			UnMovingBottomText->SetText(AvailableHackButtons[CurrentAvailableHack + 1]->GetEffectName());
		}
		else
		{
			UnMovingBottomText->SetText(FText::GetEmpty());
		}

		AvailableHackButtons[CurrentAvailableHack]->SetFocused();
		PotentialHackDescription->SetText(AvailableHackButtons[CurrentAvailableHack]->GetDescription());
	}
}

void UGUI_HackSelector::FocusPreviousAvailableHack()
{
	if (CurrentAvailableHack > 0 && !IsPlayingAnimation())
	{
		UE_LOG(LogTemp, Warning, TEXT("Bottom: %s"), *UnMovingBottomText->GetText().ToString());
		
		PlayAnimation(FocusNextHackAnim, 0, 1, EUMGSequencePlayMode::Reverse, 1, true);
		
		MovingBottomText->SetText(AvailableHackButtons[CurrentAvailableHack]->GetEffectName());

		CurrentAvailableHack--;

		AnimSelectedText->SetText(AvailableHackButtons[CurrentAvailableHack]->GetEffectName());

		if (CurrentAvailableHack - 1 < 0)
		{
			UnmovingTopBulletText->SetText(FText::GetEmpty());
		}
		else
		{
			UnmovingTopBulletText->SetText(AvailableHackButtons[CurrentAvailableHack - 1]->GetEffectName());
		}

		AvailableHackButtons[CurrentAvailableHack]->SetFocused();
		AvaialableHacksDisplay->ScrollWidgetIntoView(AvailableHackButtons[CurrentAvailableHack]);
		PotentialHackDescription->SetText(AvailableHackButtons[CurrentAvailableHack]->GetDescription());
		

	}
}

void UGUI_HackSelector::LoadSelectedToSlot()
{
	if (AvailableHacks->GetRegisteredObjects().IsEmpty() || AvailableHackButtons[CurrentAvailableHack]->IsLoaded() ||
		UnlockedHackSlots->GetRegisteredObject() == 0) return;

	if (CurrentHackBullets->GetRegisteredObject() == 0) return;

	if (LoadedHacks)
	{
		LoadedHacks->DeregisterObject(ButtonSlots[CurrentButtonSlot]->GetHack());
		LoadedHacks->RegisterObject(AvailableHackButtons[CurrentAvailableHack]->GetHack());
	}

	AvailableHackButtons[CurrentAvailableHack]->SetLoadedEnabled();

	if (UGUB_HackSelectionButton* loadedButton = ButtonSlots[CurrentButtonSlot]->GetLoadedButton())
	{
		loadedButton->SetLoadedDisabled();
	}

	ReduceBulletsIfNeeded(ButtonSlots[CurrentButtonSlot]);

	ButtonSlots[CurrentButtonSlot]->SetLoadedButton(AvailableHackButtons[CurrentAvailableHack]);

	ButtonSlots[CurrentButtonSlot]->SetHack(AvailableHackButtons[CurrentAvailableHack]->GetHack());

	SlotHackDescription->SetText(ButtonSlots[CurrentButtonSlot]->GetDescription());

	ChamberBullets[CurrentButtonSlot]->SetBrushFromTexture(SelectedFilled);
}

void UGUI_HackSelector::ReduceBulletsIfNeeded(const UGUB_HackSelectionButton* loadedButton) const
{
	if (loadedButton->IsEmpty())
	{
		ReduceRemainingBullets();
	}
}

void UGUI_HackSelector::ReduceRemainingBullets() const
{
	CurrentHackBullets->SetObject(CurrentHackBullets->GetRegisteredObject() - 1);

	UpdateRemainingBullets();
}

void UGUI_HackSelector::UpdateRemainingBullets() const
{
	const FString RemainingBulletsText = "RemainingBullets: " + FString::FromInt(CurrentHackBullets->GetRegisteredObject());

	CurrentBulletsDisplay->SetText(FText::FromString(RemainingBulletsText));
}

void UGUI_HackSelector::Exit()
{
	
	//multiply rotation speed. We do this to ensure slots finish rotating
	ChamberRotationSpeed *= 100;

	
	ButtonSlots[CurrentButtonSlot]->SetUnFocused();
	RemoveFromParent();
	CurrentAvailableHack = 0;

	for (int i = 0; i < AvailableHackButtons.Num(); i++)
	{
		AvailableHackButtons[i]->RemoveFromParent();
	}

	AvailableHackButtons.Empty();
}

void UGUI_HackSelector::NativeConstruct()
{
	Super::NativeConstruct();

	if (ButtonSlots.IsEmpty())
	{
		ButtonSlots = {HackingButton1, HackingButton2, HackingButton3, HackingButton4, HackingButton5, HackingButton6};

		ChamberBullets = {ChamberBullet1, ChamberBullet2, ChamberBullet3, ChamberBullet4, ChamberBullet5, ChamberBullet6};

		UnselectedPos = Cast<UCanvasPanelSlot>(ChamberBullet1->Slot)->GetPosition();

		//multiple construction speed so its the same after division
		ChamberRotationSpeed *= 100;
	}

	//divide rotation speed so its back to the original amount. We do this cause on exit we multiple to ensure slots finish rotating
	ChamberRotationSpeed /= 100;
	
	for (uint8 i = 0; i < ButtonSlots.Num(); i++)
	{
		if (i < UnlockedHackSlots->GetRegisteredObject())
		{
			ButtonSlots[i]->SetVisibility(ESlateVisibility::Visible);
			continue;
		}
		ButtonSlots[i]->SetVisibility(ESlateVisibility::Hidden);
	}

	if (!AvailableHacks)
	{
		return;
	}

	for (uint8 i = 0; i < AvailableHacks->GetRegisteredObjects().Num(); i++)
	{
		UGUB_HackSelectionButton* hackButton = WidgetTree->ConstructWidget<UGUB_HackSelectionButton>
		(
			BPHackingButton,
			FName("HackButton" + FString::FromInt(i))
		);

		AvaialableHacksDisplay->AddChild(hackButton);

		AvailableHackButtons.Add(hackButton);

		Cast<UScrollBoxSlot>(hackButton->Slot)->SetPadding(15);

		hackButton->SetHack(AvailableHacks->GetRegisteredObjects()[i]);
	}

	for (uint8 i = 0; i < ButtonSlots.Num(); i++)
	{
		if (LoadedHacks->GetRegisteredObjects().IsValidIndex(i))
		{
			ButtonSlots[i]->SetHack(LoadedHacks->GetRegisteredObjects()[i]);

			for (UGUB_HackSelectionButton* Button : AvailableHackButtons)
			{
				if (Button->GetHack() == LoadedHacks->GetRegisteredObjects()[i])
				{
					ButtonSlots[i]->SetLoadedButton(Button);
					Button->SetLoadedEnabled();
					break;
				}
			}
			continue;
		}
		ButtonSlots[i]->SetDisplayText(FText::FromString("Empty"));
		ButtonSlots[i]->ClearLoadedHack();
	}

	ButtonSlots[CurrentButtonSlot]->SetFocused();
	SlotHackDescription->SetText(ButtonSlots[CurrentButtonSlot]->GetDescription());

	if (!AvailableHackButtons.IsEmpty())
	{
		AvailableHackButtons[0]->SetFocused();
		PotentialHackDescription->SetText(AvailableHackButtons[0]->GetDescription());
	}

	UpdateRemainingBullets();

	if (UnlockedHackSlots->GetRegisteredObject() == 0)
	{
		for (UImage* bullet : ChamberBullets)
		{
			bullet->SetBrushFromTexture(Locked);
		}
	}
	else
	{
		for (int i = 0; i < ButtonSlots.Num(); i++)
		{
			if (i >= UnlockedHackSlots->GetRegisteredObject())
			{
				ChamberBullets[i]->SetBrushFromTexture(Locked);
				continue;
			}

			if (ButtonSlots[i]->GetHack())
			{
				ChamberBullets[i]->SetBrushFromTexture(Filled);
			}
			else
			{
				ChamberBullets[i]->SetBrushFromTexture(UnFilled);
			}
		}
		SetBulletToSelectedInstant();
	}
	

	UnmovingTopBulletText->SetText(FText::GetEmpty());

	if (AvailableHackButtons.IsValidIndex(2))
	{
		UnMovingBottomText->SetText(AvailableHackButtons[2]->GetEffectName());
	}
	else
	{
		UnMovingBottomText->SetText(FText::GetEmpty());
	}

	if (AvailableHackButtons.IsValidIndex(1))
	{
		MovingBottomText->SetText(AvailableHackButtons[1]->GetEffectName());
	}
	else
	{
		MovingBottomText->SetText(FText::GetEmpty());
	}

	if (AvailableHackButtons.IsValidIndex(0))
	{
		AnimSelectedText->SetText(AvailableHackButtons[0]->GetEffectName());
	}
	else
	{
		AnimSelectedText->SetText(FText::GetEmpty());
	}


}

void UGUI_HackSelector::RotateAllBulletsAroundCenter(const int8 RotDir, const float Amount)
{
	for (uint8 i = 0; i < ChamberBullets.Num(); i++)
	{
		const UImage* bullet = ChamberBullets[i];

		RotateBulletAroundCenter(bullet, RotDir, Amount);
	}
}

void UGUI_HackSelector::SetSelectedSprite()
{
	ChamberBullets[CurrentButtonSlot]->SetBrushFromTexture(
		ButtonSlots[CurrentButtonSlot]->GetHack() ? SelectedFilled : SelectedUnFilled);
}

void UGUI_HackSelector::PrepareCurrentBulletForSelection()
{
	UCanvasPanelSlot* CurrentSlot = Cast<UCanvasPanelSlot>(ChamberBullets[CurrentButtonSlot]->Slot);

	const FVector2D pos = CurrentSlot->GetPosition();

	//Reduce its size, as the selected sprite is bigger at the same size, so it needs to be reduced
	// It will then be lerped back up to 1
	ChamberBullets[CurrentButtonSlot]->SetRenderScale(FVector2D(0.6, 0.6));

	//Reset its position as scaling it changes its pos
	CurrentSlot->SetPosition(pos);

	//So we know where to move back to when unselecting
	UnselectedPos = pos;
	
	//The Color needs to be changed to match the sprite as well, as it should be grey,
	//but the unselcted sprite grey is white, so it now needs to be changed to grey
	ChamberBullets[CurrentButtonSlot]->SetBrushTintColor(BeforeSelectedLerpColor);
}

void UGUI_HackSelector::SetCurrentBulletToSelected(const int8 RotDir)
{
	CurrentButtonSlot = FMath::WrapExclusive<uint8>(CurrentButtonSlot, 0,  UnlockedHackSlots->GetRegisteredObject());

	//Rotate again by the amount left to rotate to take care of minor errors.
	// If not done, will add up and result in off placements on repeated rotations
	RotateAllBulletsAroundCenter(RotDir, FMath::Abs(LatestRotationGoal) - CurrentRotAmount);

	LatestRotationGoal = 0;
	CurrentRotAmount = 0;

	SetSelectedSprite();

	PrepareCurrentBulletForSelection();

	FTimerDelegate MovingChamberDel;
	MovingChamberDel.BindUFunction(this, "MoveToSelectedPositon", 0);

	MovingChamberHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(MovingChamberDel);
}

void UGUI_HackSelector::RotateToLatestChamberPos()
{
	//if its greater than zero, its 1, which due to the chamber being rotated counter-clockwise
	// means going backwards, whereas -1 is forwards
	const int8 RotDir = LatestRotationGoal >= 0 ? 1 : -1;

	const float RotAmount = ChamberRotationSpeed * GetWorld()->GetDeltaSeconds();

	CurrentRotAmount += RotAmount;

	RotateAllBulletsAroundCenter(RotDir, RotAmount);

	//Abs because we just add a positive for currentRotAmount
	if (FMath::IsNearlyEqual(CurrentRotAmount, FMath::Abs(LatestRotationGoal),RotAmount))
	{

		if (bEndChamberRotation)
		{
			SetCurrentBulletToSelected(RotDir);
			
			return;
		}
		
		MoveToNextBullet(-RotDir);
	}
	FTimerDelegate MovingChamberDel;
	MovingChamberDel.BindUFunction(this, "RotateToLatestChamberPos");

	MovingChamberHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(MovingChamberDel);
}

void UGUI_HackSelector::RotateBulletAroundCenter(const UImage* bullet, const int8 RotDir, const float RotAmount) const
{
	UCanvasPanelSlot* CurrentSlot = Cast<UCanvasPanelSlot>(bullet->Slot);

	const FVector2D center = (Cast<UCanvasPanelSlot>(ChamberParent->Slot)->GetSize() / 2) - (CurrentSlot->GetSize() / 2);

	const FVector2D Relative = CurrentSlot->GetPosition() - center;

	const float RotAmountRad = FMath::DegreesToRadians(RotDir * RotAmount);

	const float CosAngle = FMath::Cos(RotAmountRad);

	const float SinAngle = FMath::Sin(RotAmountRad);

	const float RotX = Relative.X * CosAngle - Relative.Y * SinAngle;
	const float RotY = Relative.X * SinAngle + Relative.Y * CosAngle;

	CurrentSlot->SetPosition(FVector2D(RotX, RotY) + center);
}

bool UGUI_HackSelector::LerpImageToPosition(const UImage* ToMove, const UImage* Target) const
{
	const UCanvasPanelSlot* targetSlot = Cast<UCanvasPanelSlot>(Target->Slot);

	const FVector2D target = targetSlot->GetPosition();

	if (const bool bAtTarget = LerpImageToPosition(ToMove, target)) return true;
	
	return false;
}

bool UGUI_HackSelector::LerpImageToPosition(const UImage* ToMove, const FVector2D Target) const
{
	UCanvasPanelSlot* CurrentSlot = Cast<UCanvasPanelSlot>(ToMove->Slot);

	const FVector2D newPos = FMath::Vector2DInterpConstantTo(CurrentSlot->GetPosition(), Target,
															 GetWorld()->GetDeltaSeconds(), ChamberRotationSpeed);

	CurrentSlot->SetPosition(newPos);

	if (CurrentSlot->GetPosition().Equals(Target, ChamberRotationSpeed * GetWorld()->GetDeltaSeconds()))
	{
		CurrentSlot->SetPosition(Target);
		return true;
	}
	return false;
}

bool UGUI_HackSelector::LerpImageToScale(UImage* ToMove, const FVector2D Scale) const
{
	const FVector2D newScale = FMath::Vector2DInterpConstantTo
		(
		ToMove->GetRenderTransform().Scale,
		Scale,
		GetWorld()->GetDeltaSeconds(),
		ChamberRotationSpeed / 100
		);
	
	ToMove->SetRenderScale(newScale);

	if (newScale.Equals(Scale, 1e-6))
	{
		ToMove->SetRenderScale(Scale);
		return true;
	}

	return false;
}

void UGUI_HackSelector::LerpImageToColor(float Alpha, UImage* ToMove, const FLinearColor FromColor, const FLinearColor ToColor) const
{
	const FSlateColor color = FSlateColor(
		FLinearColor::LerpUsingHSV(FromColor, ToColor, Alpha));

	ToMove->SetBrushTintColor(color);
}

void UGUI_HackSelector::MoveToSelectedPositon(float Alpha)
{
	Alpha += ColorBlendSpeed * GetWorld()->GetDeltaSeconds();

	UImage* ToMove = ChamberBullets[CurrentButtonSlot];

	const bool bAtPos = LerpImageToPosition(ToMove, SelectedSlotLocation);

	const bool bAtScale = LerpImageToScale(ToMove, FVector2D(1.f));

	LerpImageToColor(Alpha, ToMove, BeforeSelectedLerpColor.GetSpecifiedColor(), FLinearColor::White);

	if (bAtPos && bAtScale)
	{
		return;
	}
	
	FTimerDelegate MovingChamberDel;
	MovingChamberDel.BindUFunction(this, "MoveToSelectedPositon", Alpha);

	MovingChamberHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(MovingChamberDel);
}

void UGUI_HackSelector::SetBulletToSelectedInstant()
{
	UImage* ToMove = ChamberBullets[CurrentButtonSlot];

	const UCanvasPanelSlot* targetSlot = Cast<UCanvasPanelSlot>(SelectedSlotLocation->Slot);

	const FVector2D target = targetSlot->GetPosition();

	UCanvasPanelSlot* CurrentSlot = Cast<UCanvasPanelSlot>(ToMove->Slot);

	CurrentSlot->SetPosition(target);

	ToMove->SetRenderScale(FVector2D(1.f));
	
	ToMove->SetBrushTintColor(FSlateColor(FLinearColor::White));

	SetSelectedSprite();

}

void UGUI_HackSelector::SetUnselectedSprite()
{
	ChamberBullets[CurrentButtonSlot]->SetBrushFromTexture(ButtonSlots[CurrentButtonSlot]->GetHack() ? Filled : UnFilled);
}


void UGUI_HackSelector::MoveToUnselectedPosition(float Alpha, const int8 RotDir)
{
	Alpha += ColorBlendSpeed * GetWorld()->GetDeltaSeconds();

	UImage* ToMove = ChamberBullets[CurrentButtonSlot];

	const bool bAtPos = LerpImageToPosition(ToMove, UnselectedPos);

	const bool bAtScale = LerpImageToScale(ToMove, FVector2D(0.6f));

	LerpImageToColor(Alpha, ToMove, FLinearColor::White, BeforeSelectedLerpColor.GetSpecifiedColor());

	if (bAtPos && bAtScale)
	{
		SetUnselectedSprite();
		
		//reset it back to 1, so it matches sprite size
		ToMove->SetRenderScale(FVector2D(1.f));

		MoveToNextBullet(RotDir);

		FTimerDelegate MovingChamberDel;
		MovingChamberDel.BindUFunction(this, "RotateToLatestChamberPos");

		MovingChamberHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(MovingChamberDel);

		return;
	}

	FTimerDelegate MovingChamberDel;
	MovingChamberDel.BindUFunction(this, "MoveToUnselectedPosition", Alpha, RotDir);

	MovingChamberHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(MovingChamberDel);
}
