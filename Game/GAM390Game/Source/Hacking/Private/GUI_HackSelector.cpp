// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI_HackSelector.h"
#include "GUB_HackSelectionButton.h"
#include "HackEffectStore.h"
#include "Hacks/HackEffect.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ScrollBoxSlot.h"


// TO-DO: 
//Rework how rotation works to instead move each chamber by an angle.
// Except for the first point, which we lerp towards the original location of the first point. 
// OR finish rotation, then move out, could be a sperate animation?

void UGUI_HackSelector::FocusNextSlot()
{

	if (GetWorld()->GetTimerManager().IsTimerActive(MovingChamberHandle))
	{
		QuedInputs++;
		return;
	}

	ButtonSlots[CurrentButtonSlot]->SetUnFocused();

	UImage* LastBullet = ChamberBullets[CurrentButtonSlot];



	CurrentButtonSlot++;

	if (CurrentButtonSlot > UnlockedHackSlots->GetRegisteredObject() - 1)
	{
		CurrentButtonSlot = 0;
	}
	ButtonSlots[CurrentButtonSlot]->SetFocused();
	SlotHackDescription->SetText(ButtonSlots[CurrentButtonSlot]->GetDescription());

	UImage* CurrentBullet = ChamberBullets[CurrentButtonSlot];

	UCanvasPanelSlot* CurrentSlot = Cast<UCanvasPanelSlot>(CurrentBullet->Slot);

	UCanvasPanelSlot* ParentSlot = Cast<UCanvasPanelSlot>(ChamberParent->Slot);

	FVector2D CurrentPos = CurrentSlot->GetPosition();

	FVector2D target = Cast<UCanvasPanelSlot>(LastBullet->Slot)->GetPosition();

	FVector2D center = (ParentSlot->GetSize() / 2) - (CurrentSlot->GetSize() / 2);

	FVector2D dirToCenterFromCurrent = CurrentPos - center;

	FVector2D dirToCenterFromTarget = target - center;


	UE_LOG(LogTemp, Warning, TEXT("Current: %0.5f, %0.5f"), dirToCenterFromCurrent.X, dirToCenterFromCurrent.Y);
	UE_LOG(LogTemp, Warning, TEXT("Target: %0.5f, %0.5f"), dirToCenterFromTarget.X, dirToCenterFromTarget.Y);
	UE_LOG(LogTemp, Warning, TEXT("Center: %0.5f, %0.5f"), center.X, center.Y);

	float angleRad = FMath::Atan2(dirToCenterFromTarget.Y, dirToCenterFromTarget.X) - FMath::Atan2(dirToCenterFromCurrent.Y, dirToCenterFromCurrent.X);

	UE_LOG(LogTemp, Warning, TEXT("Rad: %0.5f"), angleRad);

	angleRad = FMath::UnwindRadians(angleRad);

	LatestRotationGoal = FMath::RadiansToDegrees(angleRad);


	UE_LOG(LogTemp, Warning, TEXT("Deg: %0.5f"), FMath::RadiansToDegrees(angleRad));
	UE_LOG(LogTemp, Warning, TEXT("Deg: %0.5f"), LatestRotationGoal);

	FTimerDelegate MovingChamberDel;
	MovingChamberDel.BindUFunction(this, "RotateToLatestChamberPos");

	MovingChamberHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(MovingChamberDel);
	
	LastPos = target;

	OriginalPos = CurrentPos;
}

void UGUI_HackSelector::FocusPreviousSlot()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(MovingChamberHandle))
	{
		QuedInputs--;
		return;
	}

	UImage* LastBullet = ChamberBullets[CurrentButtonSlot];
	ButtonSlots[CurrentButtonSlot]->SetUnFocused();
	CurrentButtonSlot--;

	if (CurrentButtonSlot < 0)
	{
		CurrentButtonSlot = ButtonSlots.Num() - 1;
	}
	ButtonSlots[CurrentButtonSlot]->SetFocused();
	SlotHackDescription->SetText(ButtonSlots[CurrentButtonSlot]->GetDescription());

	UImage* CurrentBullet = ChamberBullets[CurrentButtonSlot];

	UCanvasPanelSlot* CurrentSlot = Cast<UCanvasPanelSlot>(CurrentBullet->Slot);


	UCanvasPanelSlot* ParentSlot = Cast<UCanvasPanelSlot>(ChamberParent->Slot);

	FVector2D CurrentPos = CurrentSlot->GetPosition();

	FVector2D target = Cast<UCanvasPanelSlot>(LastBullet->Slot)->GetPosition() - FVector2D(48,28);

	FVector2D center = (ParentSlot->GetSize() / 2) - (CurrentSlot->GetSize() / 2);

	FVector2D dirToCenterFromCurrent = CurrentPos - center;

	FVector2D dirToCenterFromTarget = target - center;

	UE_LOG(LogTemp, Warning, TEXT("Current: %0.5f, %0.5f"), dirToCenterFromCurrent.X, dirToCenterFromCurrent.Y);
	UE_LOG(LogTemp, Warning, TEXT("Target: %0.5f, %0.5f"), dirToCenterFromTarget.X, dirToCenterFromTarget.Y);
	UE_LOG(LogTemp, Warning, TEXT("Center: %0.5f, %0.5f"), center.X, center.Y);

	float angleRad = FMath::Atan2(dirToCenterFromTarget.Y, dirToCenterFromTarget.X) - FMath::Atan2(dirToCenterFromCurrent.Y, dirToCenterFromCurrent.X);

	UE_LOG(LogTemp, Warning, TEXT("Rad: %0.5f"), angleRad);

	angleRad = FMath::UnwindRadians(angleRad);

	LatestRotationGoal = LatestRotationGoal + FMath::RadiansToDegrees(angleRad);


	UE_LOG(LogTemp, Warning, TEXT("Deg: %0.5f"), LatestRotationGoal);
	FTimerDelegate MovingChamberDel;
	MovingChamberDel.BindUFunction(this, "RotateToLatestChamberPos");

	MovingChamberHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(MovingChamberDel);

	
}

void UGUI_HackSelector::NativeConstruct()
{
	Super::NativeConstruct();

	if (ButtonSlots.IsEmpty())
	{
		ButtonSlots.Add(HackingButton1);
		ButtonSlots.Add(HackingButton2);
		ButtonSlots.Add(HackingButton3);
		ButtonSlots.Add(HackingButton4);
		ButtonSlots.Add(HackingButton5);
		ButtonSlots.Add(HackingButton6);

		ChamberBullets.Add(ChamberBullet1);
		ChamberBullets.Add(ChamberBullet2);
		ChamberBullets.Add(ChamberBullet3);
		ChamberBullets.Add(ChamberBullet4);
		ChamberBullets.Add(ChamberBullet5);
		ChamberBullets.Add(ChamberBullet6);

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

	/*ChamberParent->SetRenderTransformAngle(ChamberParent->GetRenderTransformAngle() + (ChamberRotationSpeed * GetWorld()->GetDeltaSeconds() * RotDir));

	UImage* CurrentBullet = ChamberBullets[CurrentButtonSlot];

	UImage* LastBullet = ChamberBullets[CurrentButtonSlot + RotDir];

	float SizeByFrame = FMath::Abs(100 / (LatestRotationGoal / (ChamberRotationSpeed * GetWorld()->GetDeltaSeconds())));

	float PosXByFrame = FMath::Abs(48 / (LatestRotationGoal / (ChamberRotationSpeed * GetWorld()->GetDeltaSeconds())));

	float PosYByFrame = FMath::Abs(28 / (LatestRotationGoal / (ChamberRotationSpeed * GetWorld()->GetDeltaSeconds())));


	UCanvasPanelSlot* CurrentSlot = Cast<UCanvasPanelSlot>(CurrentBullet->Slot);


	UCanvasPanelSlot* LastSlot = Cast<UCanvasPanelSlot>(LastBullet->Slot);

	CurrentSlot->SetSize(CurrentSlot->GetSize() + SizeByFrame);

	LastSlot->SetSize(LastSlot->GetSize() - SizeByFrame);*/

	//CurrentSlot->SetPosition(CurrentSlot->GetPosition() + FVector2D(PosXByFrame, PosYByFrame));


	//LastSlot->SetPosition(LastSlot->GetPosition() - FVector2D(PosXByFrame, PosYByFrame));



	if (FMath::IsNearlyEqual(CurrentRotAmount,  FMath::Abs(LatestRotationGoal), ChamberRotationSpeed * GetWorld()->GetDeltaSeconds()))
	{

		UE_LOG(LogTemp, Warning, TEXT("Lat: %0.5f"), LatestRotationGoal);
		UE_LOG(LogTemp, Warning, TEXT("Cur: %0.5f"), CurrentRotAmount);
		UE_LOG(LogTemp, Warning, TEXT("Rot: %0.5f"), FMath::Abs(LatestRotationGoal) - CurrentRotAmount);

		for (int i = 0; i < ChamberBullets.Num(); i++)
		{
			UImage* bullet = ChamberBullets[i];

			GetRotationAroundCenter(bullet, RotDir, FMath::Abs(LatestRotationGoal) - CurrentRotAmount);
		}

		LatestRotationGoal = 0;
		CurrentRotAmount = 0;



		ChamberBullets[CurrentButtonSlot]->SetBrushFromTexture(SelectedUnFilled, true);

		UCanvasPanelSlot* CurrentSlot = Cast<UCanvasPanelSlot>(ChamberBullets[CurrentButtonSlot]->Slot);

		FVector2D pos = CurrentSlot->GetPosition();

		ChamberBullets[CurrentButtonSlot]->SetRenderScale(FVector2D(0.6, 0.6));

		CurrentSlot->SetPosition(pos);

		ChamberBullets[CurrentButtonSlot]->SetBrushTintColor(BeforeSelectedLerpColor);

		FTimerDelegate MovingChamberDel;
		MovingChamberDel.BindUFunction(this, "MoveToSelectedPositon", 0);

		MovingChamberHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(MovingChamberDel);


		//ChamberParent->SetRenderTransformAngle(LatestRotationGoal);

	/*	CurrentSlot->SetSize(FVector2D(200, 200));
		LastSlot->SetSize(FVector2D(200, 200));

		LastBullet->SetBrushFromTexture(UnFilled, true);

		CurrentBullet->SetBrushFromTexture(SelectedUnFilled, true);

		CurrentBullet->SetBrushSize(FVector2D(200, 200));


		LastBullet->SetBrushSize(FVector2D(200, 200));

		LastSlot->SetPosition(LastPos);

		float CosA = FMath::Cos(LatestRotationGoal);

		float SinA = FMath::Sin(LatestRotationGoal);

		FVector2D Delta = FVector2D(48, 28);

		FVector2D RotatedDelta;
		RotatedDelta.X = Delta.X * CosA - Delta.Y * SinA;
		RotatedDelta.Y = Delta.X * SinA + Delta.Y * CosA;

		CurrentSlot->SetPosition(OriginalPos + RotatedDelta);*/


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

	CurrentSlot->SetPosition(FMath::Vector2DInterpConstantTo(CurrentSlot->GetPosition(), target, GetWorld()->GetDeltaSeconds(), ChamberRotationSpeed));

	ChamberBullets[CurrentButtonSlot]->SetRenderScale(FMath::Vector2DInterpConstantTo(ChamberBullets[CurrentButtonSlot]->GetRenderTransform().Scale, FVector2D(1, 1), GetWorld()->GetDeltaSeconds(), ChamberRotationSpeed / 100));

	FSlateColor color = FSlateColor(FLinearColor::LerpUsingHSV(BeforeSelectedLerpColor.GetSpecifiedColor(), FLinearColor::White, Alpha));

	ChamberBullets[CurrentButtonSlot]->SetBrushTintColor(color);

	if (CurrentSlot->GetPosition().Equals(target, ChamberRotationSpeed * GetWorld()->GetDeltaSeconds()))
	{
		CurrentSlot->SetPosition(target);

		ChamberBullets[CurrentButtonSlot]->SetRenderScale(FVector2D(1, 1));

		ChamberBullets[CurrentButtonSlot]->SetBrushTintColor(FSlateColor(FLinearColor::White));


		return;
	}


	FTimerDelegate MovingChamberDel;
	MovingChamberDel.BindUFunction(this, "MoveToSelectedPositon", Alpha);

	MovingChamberHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(MovingChamberDel);

	
}

void UGUI_HackSelector::FocusNextAvailableHack()
{
	if (CurrentAvailableHack < AvailableHackButtons.Num() - 1)
	{
		AvailableHackButtons[CurrentAvailableHack]->SetUnFocused();
		CurrentAvailableHack++;
		AvailableHackButtons[CurrentAvailableHack]->SetFocused();
		AvaialableHacksDisplay->ScrollWidgetIntoView(AvailableHackButtons[CurrentAvailableHack]);
		PotentialHackDescription->SetText(AvailableHackButtons[CurrentAvailableHack]->GetDescription());
	}
}

void UGUI_HackSelector::FocusPreviousAvailableHack()
{
	if (CurrentAvailableHack > 0)
	{
		AvailableHackButtons[CurrentAvailableHack]->SetUnFocused();
		CurrentAvailableHack--;
		AvailableHackButtons[CurrentAvailableHack]->SetFocused();
		AvaialableHacksDisplay->ScrollWidgetIntoView(AvailableHackButtons[CurrentAvailableHack]);
		PotentialHackDescription->SetText(AvailableHackButtons[CurrentAvailableHack]->GetDescription());
	}
}

void UGUI_HackSelector::LoadSelectedToSlot()
{
	if (AvailableHacks->GetRegisteredObjects().IsEmpty() || AvailableHackButtons[CurrentAvailableHack]->IsLoaded() || UnlockedHackSlots->GetRegisteredObject() == 0)
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
