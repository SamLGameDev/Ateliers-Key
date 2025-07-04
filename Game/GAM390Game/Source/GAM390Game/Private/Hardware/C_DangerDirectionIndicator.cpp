// Fill out your copyright notice in the Description page of Project Settings.


#include "Hardware/C_DangerDirectionIndicator.h"
#include "DamageSystem.h"
#include "DamageResponse.h"
#include "Hardware/GUI_DamageLocationIndicator.h"
#include "BP_GeneralFunctions.h"
#include "GameFramework/Character.h"

void UC_DangerDirectionIndicator::EnableAbility()
{
	GetOwner()->GetComponentByClass<UDamageSystem>()->OnDamageResponse.AddDynamic(this, &UC_DangerDirectionIndicator::StartDamageIndicator);
	DamageIndicator = CreateWidget<UGUI_DamageLocationIndicator>(GetWorld(), DIClass, "DamageIndicator");
	DamageIndicator->AddToViewport();
	DamageIndicator->SetHidden();
}

void UC_DangerDirectionIndicator::StartDamageIndicator(EDamageResponse DamageResponse, AActor* Source)
{
	UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(Source->GetComponentByClass(UPrimitiveComponent::StaticClass()));

	if (Prim && Prim->WasRecentlyRendered(0.1f))
	{
		return;
	}
	DamageIndicator->SetVisible();

	CalculateDirection(Source);

	FTimerDelegate TickDel;

	TickDel.BindUFunction(this, NAMEOF(CalculateDirection), Source);

	GetWorld()->GetTimerManager().ClearTimer(TickHandle);

	GetWorld()->GetTimerManager().SetTimer(TickHandle, TickDel, 0.01f, true, -1);

	FTimerDelegate FadeDel;

	FadeDel.BindUFunction(this, NAMEOF(HideIndicator), TickHandle);

	GetWorld()->GetTimerManager().ClearTimer(FadeHandle);

	GetWorld()->GetTimerManager().SetTimer(FadeHandle, FadeDel, FadeTime, false, -1);

}

void UC_DangerDirectionIndicator::CalculateDirection(AActor* Source)
{
	const FVector dirToDealer = (Source->GetActorLocation() - GetOwner()->GetActorLocation()).GetSafeNormal();
	const FVector forwardDir = GetOwner()->GetActorForwardVector();
	const FVector upDir = GetOwner()->GetActorRightVector();

	Print("%0.5f %0.5f dir why", forwardDir.X, forwardDir.Y);


	

	DamageIndicator->RotateToFace(dirToDealer, forwardDir, upDir);


}

void UC_DangerDirectionIndicator::HideIndicator()
{
	DamageIndicator->SetHidden();

	GetWorld()->GetTimerManager().ClearTimer(TickHandle);
}
