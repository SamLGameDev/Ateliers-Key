// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseArmPart.h"
#include "BaseArchetype.h"

void ABaseArmPart::PostLoad()
{
	Super::PostLoad();
	if (!Archetypes.IsEmpty())
	{
		for (UBaseArchetype* Archetype : Archetypes)
		{
			Archetype->RegisterArmPart(this);
		}
	}

}