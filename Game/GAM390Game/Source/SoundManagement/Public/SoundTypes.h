// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ESoundUse : uint8
{
	Any,
	Ambient,
	Music,
	UI,
	Cinematic,
};
