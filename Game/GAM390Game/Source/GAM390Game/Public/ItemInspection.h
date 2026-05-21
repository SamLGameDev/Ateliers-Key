// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemInspection.generated.h"

USTRUCT(BlueprintType)
struct FItemInspection{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inspection")
	UStaticMesh* SM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inspection")
	bool UseSkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inspection")
	USkeletalMesh* SKM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inspection")
	UAnimationAsset* AnimToPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inspection")
	FRotator RotationOffset; 
};
