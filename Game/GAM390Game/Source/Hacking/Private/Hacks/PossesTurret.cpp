// Fill out your copyright notice in the Description page of Project Settings.


#include "Hacks/PossesTurret.h"
#include <HackableTurret.h>

void UPossesTurret::ExecuteHack(const FHackInfo& HackInfo)
{
	Super::ExecuteHack(HackInfo);

	AHackableTurret* obj = Cast<AHackableTurret>(HackInfo.HackedObject);

	if (!obj)
	{
		return;
	}

	obj->GetWorld()->GetFirstPlayerController()->Possess(obj);

	obj->StartCountdown();

	obj->DamageSystem->TeamNumber = 0;
}
