// Fill out your copyright notice in the Description page of Project Settings.


#include "Hacks/SelfDestruct.h"

void USelfDestruct::ExecuteHack(const FHackInfo& HackInfo)
{
	Super::ExecuteHack(HackInfo);

	Cast<AActor>(HackInfo.HackedObject)->Destroy();
}
