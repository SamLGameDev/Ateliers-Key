// Fill out your copyright notice in the Description page of Project Settings.

#include "GUI_HackSelector.h"

#include "BP_GeneralFunctions.h"
#include "GUB_HackSelectionButton.h"
#include "HackEffectStore.h"
#include "Hacks/HackEffect.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ScrollBoxSlot.h"

void UGUI_HackSelector::FocusNextSlot()
{
    if (UnlockedHackSlots->GetRegisteredObject() <= 1) return;
    
	
	uint8 index = FMath::WrapExclusive<uint8>(CurrentButtonSlot + QuedInputs, 0, UnlockedHackSlots->GetRegisteredObject());

	ButtonSlots[index]->SetUnFocused();

	UImage* LastBullet = ChamberBullets[index];

	QuedInputs++;

	index = FMath::WrapExclusive<uint8>(CurrentButtonSlot + QuedInputs, 0, UnlockedHackSlots->GetRegisteredObject());

	if (index >= UnlockedHackSlots->GetRegisteredObject())
	{
		index = 0;
	}

	ButtonSlots[index]->SetFocused();
	SlotHackDescription->SetText(ButtonSlots[index]->GetDescription());

	UImage* CurrentBullet = ChamberBullets[index];

	UCanvasPanelSlot* CurrentSlot = Cast<UCanvasPanelSlot>(CurrentBullet->Slot);

	UCanvasPanelSlot* ParentSlot = Cast<UCanvasPanelSlot>(ChamberParent->Slot);

	FVector2D CurrentPos = CurrentSlot->GetPosition();

	FVector2D target = Cast<UCanvasPanelSlot>(LastBullet->Slot)->GetPosition();

	FVector2D center = (ParentSlot->GetSize() / 2) - (CurrentSlot->GetSize() / 2);

	FVector2D dirToCenterFromCurrent = CurrentPos - center;

	FVector2D dirToCenterFromTarget = target - center;

	const float angleRad = FMath::Atan2(dirToCenterFromTarget.Y, dirToCenterFromTarget.X) - FMath::Atan2(
		dirToCenterFromCurrent.Y, dirToCenterFromCurrent.X);

	UE_LOG(LogTemp, Warning, TEXT("Rad: %0.5f"), angleRad);
	
	float angleDeg = FMath::RadiansToDegrees(angleRad);

	if (angleDeg > 0)
	{
		angleDeg = -360 + angleDeg;
	}

	LatestRotationGoal += angleDeg;

	if (GetWorld()->GetTimerManager().IsTimerActive(MovingChamberHandle))
	{
		return;
	}

	FTimerDelegate MovingChamberDel;
	MovingChamberDel.BindUFunction(this, "MoveToUnselectedPosition", 0);

	MovingChamberHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(MovingChamberDel);

	LastPos = target;

	OriginalPos = CurrentPos;
}

void UGUI_HackSelector::FocusPreviousSlot()
{
	if (UnlockedHackSlots->GetRegisteredObject() <= 1) return;
	
	uint8 index = FMath::WrapExclusive<uint8>(CurrentButtonSlot + QuedInputs, 0, UnlockedHackSlots->GetRegisteredObject());

	ButtonSlots[index]->SetUnFocused();

	UImage* LastBullet = ChamberBullets[index];

	QuedInputs--;

	index = FMath::WrapExclusive<uint8>(CurrentButtonSlot + QuedInputs, 0, UnlockedHackSlots->GetRegisteredObject());

	ButtonSlots[CurrentButtonSlot]->SetFocused();
	SlotHackDescription->SetText(ButtonSlots[index]->GetDescription());

	UImage* CurrentBullet = ChamberBullets[index];

	UCanvasPanelSlot* CurrentSlot = Cast<UCanvasPanelSlot>(CurrentBullet->Slot);

	UCanvasPanelSlot* ParentSlot = Cast<UCanvasPanelSlot>(ChamberParent->Slot);

	FVector2D CurrentPos = CurrentSlot->GetPosition();

	FVector2D target = Cast<UCanvasPanelSlot>(LastBullet->Slot)->GetPosition() - FVector2D(48, 28);

	FVector2D center = (ParentSlot->GetSize() / 2) - (CurrentSlot->GetSize() / 2);

	FVector2D dirToCenterFromCurrent = CurrentPos - center;

	FVector2D dirToCenterFromTarget = target - center;

	float angleRad = FMath::Atan2(dirToCenterFromTarget.Y, dirToCenterFromTarget.X) - FMath::Atan2(
		dirToCenterFromCurrent.Y, dirToCenterFromCurrent.X);
	
	angleRad = FMath::UnwindRadians(angleRad);

	float angleDeg = FMath::RadiansToDegrees(angleRad);

	if (angleDeg < 0)
	{
		angleDeg = 360 + angleDeg;
	}

	LatestRotationGoal += angleDeg;
	
	FTimerDelegate MovingChamberDel;
	MovingChamberDel.BindUFunction(this, "MoveToUnselectedPosition", 0);

	MovingChamberHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(MovingChamberDel);
}

void UGUI_HackSelector::NativeConstruct()
{
	Super::NativeConstruct();

	if (ButtonSlots.IsEmpty())
	{
		ButtonSlots = {HackingButton1, HackingButton2, HackingButton3, HackingButton4, HackingButton5, HackingButton6};

		ChamberBullets = {ChamberBullet1, ChamberBullet2, ChamberBullet3, ChamberBullet4, ChamberBullet5, ChamberBullet6};

		UnselectedPos = Cast<UCanvasPanelSlot>(ChamberBullet1->Slot)->GetPosition();
	}

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

	for (int i = 0; i < AvailableHacks->GetRegisteredObjects().Num(); i++)
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

	for (int i = 0; i < ButtonSlots.Num(); i++)
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

	ButtonSlots[0]->SetFocused();
	SlotHackDescription->SetText(ButtonSlots[0]->GetDescription());

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
		return;
	}

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

	SetBulletToSelected();

	ChamberBullet1->SetBrushFromTexture(ButtonSlots[0]->GetHack() ? SelectedFilled : SelectedUnFilled);
}

void UGUI_HackSelector::RotateToLatestChamberPos()
{
	int RotDir = LatestRotationGoal >= 0 ? 1 : -1;

	CurrentRotAmount += ChamberRotationSpeed * GetWorld()->GetDeltaSeconds();

	for (int i = 0; i < ChamberBullets.Num(); i++)
	{
		UImage* bullet = ChamberBullets[i];

		GetRotationAroundCenter(bullet, RotDir, ChamberRotationSpeed * GetWorld()->GetDeltaSeconds());
	}

	if (FMath::IsNearlyEqual(CurrentRotAmount, FMath::Abs(LatestRotationGoal),
	                         ChamberRotationSpeed * GetWorld()->GetDeltaSeconds()))
	{
		CurrentButtonSlot = FMath::WrapExclusive(QuedInputs + CurrentButtonSlot, 0, 6);

		if (CurrentButtonSlot >= UnlockedHackSlots->GetRegisteredObject())
		{
			CurrentButtonSlot = RotDir == -1 ? 0 : UnlockedHackSlots->GetRegisteredObject() - 1;
		}

		UE_LOG(LogTemp, Warning, TEXT("But: %d"), CurrentButtonSlot);
		UE_LOG(LogTemp, Warning, TEXT("Cur: %0.5f"), CurrentRotAmount);
		UE_LOG(LogTemp, Warning, TEXT("Rot: %0.5f"), FMath::Abs(LatestRotationGoal) - CurrentRotAmount);

		for (int i = 0; i < ChamberBullets.Num(); i++)
		{
			UImage* bullet = ChamberBullets[i];

			GetRotationAroundCenter(bullet, RotDir, FMath::Abs(LatestRotationGoal) - CurrentRotAmount);
		}

		LatestRotationGoal = 0;
		CurrentRotAmount = 0;
		QuedInputs = 0;

		ChamberBullets[CurrentButtonSlot]->SetBrushFromTexture(
			ButtonSlots[CurrentButtonSlot]->GetHack() ? SelectedFilled : SelectedUnFilled);

		UCanvasPanelSlot* CurrentSlot = Cast<UCanvasPanelSlot>(ChamberBullets[CurrentButtonSlot]->Slot);

		FVector2D pos = CurrentSlot->GetPosition();

		ChamberBullets[CurrentButtonSlot]->SetRenderScale(FVector2D(0.6, 0.6));

		CurrentSlot->SetPosition(pos);

		UnselectedPos = pos;

		ChamberBullets[CurrentButtonSlot]->SetBrushTintColor(BeforeSelectedLerpColor);

		FTimerDelegate MovingChamberDel;
		MovingChamberDel.BindUFunction(this, "MoveToSelectedPositon", 0);

		MovingChamberHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(MovingChamberDel);

		return;
	}
	FTimerDelegate MovingChamberDel;
	MovingChamberDel.BindUFunction(this, "RotateToLatestChamberPos");

	MovingChamberHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(MovingChamberDel);
}

void UGUI_HackSelector::GetRotationAroundCenter(UImage* bullet, int RotDir, float RotAmount)
{
	UCanvasPanelSlot* CurrentSlot = Cast<UCanvasPanelSlot>(bullet->Slot);

	FVector2D center = (Cast<UCanvasPanelSlot>(ChamberParent->Slot)->GetSize() / 2) - (CurrentSlot->GetSize() / 2);

	FVector2D Relative = CurrentSlot->GetPosition() - center;

	float CosAngle = FMath::Cos(FMath::DegreesToRadians(RotAmount * RotDir));

	float SinAngle = FMath::Sin(FMath::DegreesToRadians(RotAmount * RotDir));

	float RotX = Relative.X * CosAngle - Relative.Y * SinAngle;
	float RotY = Relative.X * SinAngle + Relative.Y * CosAngle;

	CurrentSlot->SetPosition(FVector2D(RotX, RotY) + center);
}

void UGUI_HackSelector::MoveToSelectedPositon(float Alpha)
{
	Alpha += ColorBlendSpeed * GetWorld()->GetDeltaSeconds();

	UCanvasPanelSlot* targetSlot = Cast<UCanvasPanelSlot>(SelectedSlotLocation->Slot);

	FVector2D target = targetSlot->GetPosition();
	UCanvasPanelSlot* CurrentSlot = Cast<UCanvasPanelSlot>(ChamberBullets[CurrentButtonSlot]->Slot);

	CurrentSlot->SetPosition(FMath::Vector2DInterpConstantTo(CurrentSlot->GetPosition(), target,
	                                                         GetWorld()->GetDeltaSeconds(), ChamberRotationSpeed));

	ChamberBullets[CurrentButtonSlot]->SetRenderScale(FMath::Vector2DInterpConstantTo(
		ChamberBullets[CurrentButtonSlot]->GetRenderTransform().Scale, FVector2D(1, 1), GetWorld()->GetDeltaSeconds(),
		ChamberRotationSpeed / 100));

	FSlateColor color = FSlateColor(
		FLinearColor::LerpUsingHSV(BeforeSelectedLerpColor.GetSpecifiedColor(), FLinearColor::White, Alpha));

	ChamberBullets[CurrentButtonSlot]->SetBrushTintColor(color);

	if (CurrentSlot->GetPosition().Equals(target, ChamberRotationSpeed * GetWorld()->GetDeltaSeconds()))
	{
		SetBulletToSelected();
		return;
	}

	FTimerDelegate MovingChamberDel;
	MovingChamberDel.BindUFunction(this, "MoveToSelectedPositon", Alpha);

	MovingChamberHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(MovingChamberDel);
}

void UGUI_HackSelector::SetBulletToSelected()
{
	UCanvasPanelSlot* targetSlot = Cast<UCanvasPanelSlot>(SelectedSlotLocation->Slot);

	FVector2D target = targetSlot->GetPosition();
	UCanvasPanelSlot* CurrentSlot = Cast<UCanvasPanelSlot>(ChamberBullets[CurrentButtonSlot]->Slot);

	CurrentSlot->SetPosition(target);

	ChamberBullets[CurrentButtonSlot]->SetRenderScale(FVector2D(1, 1));

	ChamberBullets[CurrentButtonSlot]->SetBrushTintColor(FSlateColor(FLinearColor::White));

	LatestRotationGoal = 0;
	CurrentRotAmount = 0;
	QuedInputs = 0;
}

void UGUI_HackSelector::SetBulletToUnSelected()
{
	UImage* bullet = ChamberBullets[CurrentButtonSlot];

	UCanvasPanelSlot* CurrentSlot = Cast<UCanvasPanelSlot>(bullet->Slot);

	CurrentSlot->SetPosition(UnselectedPos);

	bullet->SetRenderScale(FVector2D(1, 1));

	bullet->SetBrushTintColor(FSlateColor(FLinearColor::White));

	bullet->SetBrushFromTexture(ButtonSlots[CurrentButtonSlot]->GetHack() ? Filled : UnFilled);
}

void UGUI_HackSelector::MoveToUnselectedPosition(float Alpha)
{
	Alpha += ColorBlendSpeed * GetWorld()->GetDeltaSeconds();

	UImage* bullet = ChamberBullets[CurrentButtonSlot];

	UCanvasPanelSlot* CurrentSlot = Cast<UCanvasPanelSlot>(bullet->Slot);

	CurrentSlot->SetPosition(FMath::Vector2DInterpConstantTo(CurrentSlot->GetPosition(), UnselectedPos,
	                                                         GetWorld()->GetDeltaSeconds(), ChamberRotationSpeed));

	bullet->SetRenderScale(FMath::Vector2DInterpConstantTo(bullet->GetRenderTransform().Scale, FVector2D(0.6, 0.6),
	                                                       GetWorld()->GetDeltaSeconds(), ChamberRotationSpeed / 100));

	FSlateColor color = FSlateColor(
		FLinearColor::LerpUsingHSV(FLinearColor::White, BeforeSelectedLerpColor.GetSpecifiedColor(), Alpha));

	bullet->SetBrushTintColor(color);

	Print("CurrentSlotPos: %0.5f, %0.5f", CurrentSlot->GetPosition().X, CurrentSlot->GetPosition().Y);
	Print("UnselectedPos: %0.5f, %0.5f", UnselectedPos.X, UnselectedPos.Y);

	if (CurrentSlot->GetPosition().Equals(UnselectedPos, ChamberRotationSpeed * GetWorld()->GetDeltaSeconds()))
	{
		SetBulletToUnSelected();

		FTimerDelegate MovingChamberDel;
		MovingChamberDel.BindUFunction(this, "RotateToLatestChamberPos");

		MovingChamberHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(MovingChamberDel);

		return;
	}

	FTimerDelegate MovingChamberDel;
	MovingChamberDel.BindUFunction(this, "MoveToUnselectedPosition", Alpha);

	MovingChamberHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(MovingChamberDel);
}

void UGUI_HackSelector::FocusNextAvailableHack()
{
	if (CurrentAvailableHack < AvailableHackButtons.Num() - 1)
	{
		PlayAnimation(FocusNextHackAnim, 0, 1, EUMGSequencePlayMode::Forward, 1, true);
		CurrentAvailableHack++;
		AvailableHackButtons[CurrentAvailableHack]->SetFocused();
		//AvaialableHacksDisplay->ScrollWidgetIntoView(AvailableHackButtons[CurrentAvailableHack]);
		PotentialHackDescription->SetText(AvailableHackButtons[CurrentAvailableHack]->GetDescription());
	}
}

void UGUI_HackSelector::FocusPreviousAvailableHack()
{
	if (CurrentAvailableHack > 0)
	{
		PlayAnimation(FocusNextHackAnim, 0, 1, EUMGSequencePlayMode::Reverse, 1, true);
		AvailableHackButtons[CurrentAvailableHack]->SetUnFocused();
		CurrentAvailableHack--;
		AvailableHackButtons[CurrentAvailableHack]->SetFocused();
		AvaialableHacksDisplay->ScrollWidgetIntoView(AvailableHackButtons[CurrentAvailableHack]);
		PotentialHackDescription->SetText(AvailableHackButtons[CurrentAvailableHack]->GetDescription());
	}
}

void UGUI_HackSelector::LoadSelectedToSlot()
{
	if (AvailableHacks->GetRegisteredObjects().IsEmpty() || AvailableHackButtons[CurrentAvailableHack]->IsLoaded() ||
		UnlockedHackSlots->GetRegisteredObject() == 0)
	{
		return;
	}

	if (CurrentHackBullets->GetRegisteredObject() == 0)
	{
		return;
	}

	if (LoadedHacks)
	{
		LoadedHacks->DeregisterObject(ButtonSlots[CurrentButtonSlot]->GetHack());
		LoadedHacks->RegisterObject(AvailableHackButtons[CurrentAvailableHack]->GetHack());
	}

	AvailableHackButtons[CurrentAvailableHack]->SetLoadedEnabled();

	UGUB_HackSelectionButton* loadedButton = ButtonSlots[CurrentButtonSlot]->GetLoadedButton();
	if (loadedButton)
	{
		loadedButton->SetLoadedDisabled();
	}

	ReduceBulletsIfNeeded(ButtonSlots[CurrentButtonSlot]);

	ButtonSlots[CurrentButtonSlot]->SetLoadedButton(AvailableHackButtons[CurrentAvailableHack]);

	ButtonSlots[CurrentButtonSlot]->SetHack(AvailableHackButtons[CurrentAvailableHack]->GetHack());

	SlotHackDescription->SetText(ButtonSlots[CurrentButtonSlot]->GetDescription());

	ChamberBullets[CurrentButtonSlot]->SetBrushFromTexture(SelectedFilled);
}

void UGUI_HackSelector::ReduceBulletsIfNeeded(UGUB_HackSelectionButton* loadedButton)
{
	if (loadedButton->IsEmpty())
	{
		ReduceRemainngBullets();
	}
}

void UGUI_HackSelector::ReduceRemainngBullets()
{
	CurrentHackBullets->SetObject(CurrentHackBullets->GetRegisteredObject() - 1);

	UpdateRemainingBullets();
}

void UGUI_HackSelector::UpdateRemainingBullets()
{
	FString RemainingBulletsText = "RemainingBullets: " + FString::FromInt(CurrentHackBullets->GetRegisteredObject());

	CurrentBulletsDisplay->SetText(FText::FromString((RemainingBulletsText)));
}

void UGUI_HackSelector::Exit()
{
	ButtonSlots[CurrentButtonSlot]->SetUnFocused();
	RemoveFromParent();
	CurrentAvailableHack = 0;
	CurrentButtonSlot = 0;

	for (int i = 0; i < AvailableHackButtons.Num(); i++)
	{
		AvailableHackButtons[i]->RemoveFromParent();
	}

	AvailableHackButtons.Empty();
}
