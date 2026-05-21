// Fill out your copyright notice in the Description page of Project Settings.


#include "Hardware/C_DangerDirectionIndicator.h"
#include "DamageSystem.h"
#include "DamageResponse.h"
#include "Hardware/GUI_DamageLocationIndicator.h"
#include "BP_GeneralFunctions.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

void UC_DangerDirectionIndicator::EnableAbility()
{
	GetOwner()->GetComponentByClass<UDamageSystem>()->OnDamageResponse.AddDynamic(this, &UC_DangerDirectionIndicator::StartDamageIndicator);
	
	for (uint8 i = 0; i < NumberOfIndicators; i++)
	{
		UGUI_DamageLocationIndicator* DamageIndicator = CreateWidget<UGUI_DamageLocationIndicator>(GetWorld(), DIClass, FName("DamageIndicator" + FString::FromInt(i)));
		DamageIndicator->AddToViewport();
		DamageIndicator->SetHidden();
		UnusedIndicators.Add(DamageIndicator);
	}
}

void UC_DangerDirectionIndicator::StartDamageIndicator(EDamageResponse DamageResponse, AActor* Source)
{
	const UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(Source->GetComponentByClass(UPrimitiveComponent::StaticClass()));

	const float lastRenderTime = Prim->GetLastRenderTimeOnScreen();

	const float TimeSinceRender = GetWorld()->GetTime().GetWorldTimeSeconds() - lastRenderTime;

	if (!(lastRenderTime < 0 || TimeSinceRender >= 1))
	{
		return;
	}

	UGUI_DamageLocationIndicator* DamageIndicator = GetIndicator();

	DamageIndicator->StartRotation(Source, this->GetOwner(), UnusedIndicators, FadeTime);

}

UGUI_DamageLocationIndicator* UC_DangerDirectionIndicator::GetIndicator()
{
	UGUI_DamageLocationIndicator* DamageIndicator;
	if (!UnusedIndicators.IsEmpty())
	{
		DamageIndicator = UnusedIndicators[0];
		UnusedIndicators.RemoveAt(0);
		ActiveIndicators.Add(DamageIndicator);
		return DamageIndicator;
	}
	DamageIndicator = ActiveIndicators[0];
	GetWorld()->GetTimerManager().ClearTimer(DamageIndicator->TickHandle);
	GetWorld()->GetTimerManager().ClearTimer(DamageIndicator->FadeHandle);
	ActiveIndicators.RemoveAt(0);
	ActiveIndicators.Add(DamageIndicator);
	return DamageIndicator;
}
