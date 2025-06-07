// Fill out your copyright notice in the Description page of Project Settings.


#include "Hacks/SelfDestruct.h"

void USelfDestruct::ExecuteHack(UObject* HackedObject)
{
	Cast<AActor>(HackedObject)->Destroy();
}
