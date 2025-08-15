// Fill out your copyright notice in the Description page of Project Settings.


#include "Hacks/PossesTurret.h"


void UPossesTurret::ExecuteHack(UObject* HackedObject)
{
	Super::ExecuteHack(HackedObject);

	APawn* obj = Cast<APawn>(HackedObject);

	if (obj->ActorHasTag("Turret"))
	{
		obj->GetWorld()->GetFirstPlayerController()->Possess(obj);
	}
}
