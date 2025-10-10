// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hacks/HackEffect.h"
#include "SelfDestruct.generated.h"

/**
 * 
 */
UCLASS()
class HACKING_API USelfDestruct : public UHackEffect
{
	GENERATED_BODY()

public:
	virtual void ExecuteHack(const FHackInfo& HackInfo) override;
};
