// Fill out your copyright notice in the Description page of Project Settings.


#include "Hardware/GUI_DamageLocationIndicator.h"

void UGUI_DamageLocationIndicator::RotateToFace(const FVector Direction)
{
	float X = Direction.X;
	float Y = Direction.Z;
	float Angle = FMath::Atan2(Y, X) * 180 / PI;

	Canvas->SetRenderTransformAngle(Angle);
}
