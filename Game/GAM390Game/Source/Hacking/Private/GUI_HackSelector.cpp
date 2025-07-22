// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI_HackSelector.h"
#include "GUB_HackSelectionButton.h"
#include "HackEffectStore.h"
#include "Hacks/HackEffect.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ScrollBoxSlot.h"


void UGUI_HackSelector::FocusNextSlot()
{
	if (CurrentButtonSlot < UnlockedHackSlots->GetRegisteredObject() - 1)
	{
		ButtonSlots[CurrentButtonSlot]->SetUnFocused();

		UImage* LastBullet = ChamberBullets[CurrentButtonSlot];

		CurrentButtonSlot++;
		ButtonSlots[CurrentButtonSlot]->SetFocused();
		SlotHackDescription->SetText(ButtonSlots[CurrentButtonSlot]->GetDescription());

		UImage* CurrentBullet = ChamberBullets[CurrentButtonSlot];

		UCanvasPanelSlot* CurrentSlot = Cast<UCanvasPanelSlot>(CurrentBullet->Slot);

		UCanvasPanelSlot* ParentSlot = Cast<UCanvasPanelSlot>(ChamberParent->Slot);

		FVector2D CurrentPos = CurrentSlot->GetPosition();

		FVector2D target = Cast<UCanvasPanelSlot>(LastBullet->Slot)->GetPosition();

		FVector2D center = (ParentSlot->GetSize() / 2) - (CurrentSlot->GetSize()/2);

		FVector2D dirToCenterFromCurrent = CurrentPos - center;

		FVector2D dirToCenterFromTarget = target - center;

		UE_LOG(LogTemp, Warning, TEXT("Current: %0.5f, %0.5f"), dirToCenterFromCurrent.X, dirToCenterFromCurrent.Y);
		UE_LOG(LogTemp, Warning, TEXT("Target: %0.5f, %0.5f"), dirToCenterFromTarget.X, dirToCenterFromTarget.Y);
		UE_LOG(LogTemp, Warning, TEXT("Center: %0.5f, %0.5f"), center.X, center.Y);

		float angleRad = FMath::Atan2(dirToCenterFromTarget.Y, dirToCenterFromTarget.X) - FMath::Atan2(dirToCenterFromCurrent.Y, dirToCenterFromCurrent.X);

		UE_LOG(LogTemp, Warning, TEXT("Rad: %0.5f"), angleRad);


		LatestRotationGoal = FMath::RadiansToDegrees(angleRad) + LatestRotationGoal;

		if (GetWorld()->GetTimerManager().IsTimerActive(MovingChamberHandle))
		{
			return;
		}

		FTimerDelegate MovingChamberDel;
		MovingChamberDel.BindUFunction(this, "RotateToLatestChamberPos");

		MovingChamberHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(MovingChamberDel);


	}
}

void UGUI_HackSelector::FocusPreviousSlot()
{
	if (CurrentButtonSlot > 0)
	{
		ButtonSlots[CurrentButtonSlot]->SetUnFocused();
		CurrentButtonSlot--;
		ButtonSlots[CurrentButtonSlot]->SetFocused();
		SlotHackDescription->SetText(ButtonSlots[CurrentButtonSlot]->GetDescription());
	}
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

		ChamberBullets.Add(ChamberBullet1);
		ChamberBullets.Add(ChamberBullet2);
		ChamberBullets.Add(ChamberBullet3);
		ChamberBullets.Add(ChamberBullet4);
		ChamberBullets.Add(ChamberBullet5);

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
	ChamberParent->SetRenderTransformAngle(ChamberParent->GetRenderTransformAngle() - (ChamberRotationSpeed * GetWorld()->GetDeltaSeconds()));

	if (ChamberParent->GetRenderTransformAngle() <= LatestRotationGoal)
	{
		ChamberParent->SetRenderTransformAngle(LatestRotationGoal);
		return;
	}
	FTimerDelegate MovingChamberDel;
	MovingChamberDel.BindUFunction(this, "RotateToLatestChamberPos");

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
