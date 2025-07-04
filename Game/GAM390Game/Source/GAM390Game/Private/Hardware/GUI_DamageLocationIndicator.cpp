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
