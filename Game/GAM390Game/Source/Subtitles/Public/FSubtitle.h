// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSubtitle.generated.h"


USTRUCT(BlueprintType)
struct FSubtitle : public FTableRowBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subtitle")
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subtitle")
	float Time;
};
