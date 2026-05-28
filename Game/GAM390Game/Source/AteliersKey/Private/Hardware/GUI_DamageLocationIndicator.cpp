// Fill out your copyright notice in the Description page of Project Settings.


#include "Hardware/GUI_DamageLocationIndicator.h"

void UGUI_DamageLocationIndicator::RotateToFace(const FVector Direction, const FVector ForwardDir, const FVector UpDir)
{
	const float X = FVector::DotProduct(ForwardDir, Direction);
	const float Y = FVector::DotProduct(UpDir, Direction);

	float Angle = FMath::Atan2(Y, X) * 180 / PI;

	Canvas->SetRenderTransformAngle(Angle);
}

void UGUI_DamageLocationIndicator::SetHidden()
{
	SetVisibility(ESlateVisibility::Hidden);

}

void UGUI_DamageLocationIndicator::SetVisible()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UGUI_DamageLocationIndicator::StartRotation(const AActor* Source, const AActor* Hit, TArray<UGUI_DamageLocationIndicator*>& UnusedIndicators, const float FadeTime)
{
	SetVisible();

	TickRotation(Source, Hit);

	FTimerDelegate TickDel;

	TickDel.BindUFunction(this, "TickRotation", Source, Hit);

	GetWorld()->GetTimerManager().SetTimer(TickHandle, TickDel, 0.01f, true, -1);

	FTimerDelegate FadeDel;

	FadeDel.BindUFunction(this, "EndRotation", UnusedIndicators);

	GetWorld()->GetTimerManager().SetTimer(FadeHandle, FadeDel, FadeTime, false, -1);

}

void UGUI_DamageLocationIndicator::TickRotation(const AActor* Source, const AActor* Hit)
{
	const FVector dirToDealer = (Source->GetActorLocation() - Hit->GetActorLocation()).GetSafeNormal();
	const FVector forwardDir = Hit->GetActorForwardVector();
	const FVector upDir = Hit->GetActorRightVector();

	RotateToFace(dirToDealer, forwardDir, upDir);
}

void UGUI_DamageLocationIndicator::EndRotation(TArray<UGUI_DamageLocationIndicator*>& UnusedIndicators)
{
	SetHidden();

	GetWorld()->GetTimerManager().ClearTimer(TickHandle);

	UnusedIndicators.Add(this);
}
