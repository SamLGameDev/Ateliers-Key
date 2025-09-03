// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hacks/HackEffect.h"
#include "PossesTurret.generated.h"

/**
 * 
 */
UCLASS()
class HACKING_API UPossesTurret : public UHackEffect
{
	GENERATED_BODY()

public:
	virtual void ExecuteHack(UObject* HackedObject) override;
};
