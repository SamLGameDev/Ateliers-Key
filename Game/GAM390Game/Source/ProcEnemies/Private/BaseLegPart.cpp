// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLegPart.h"
#include "BaseArchetype.h"
#include "Pawns/BaseProcEnemy.h"

void ABaseLegPart::AttatchPart(ABaseProcEnemy* Enemy)
{
	Enemy->SetLegs(this);
	const FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);

	AttachToActor(Enemy, Rules, Enemy->GetHeadSocketName());
}

void ABaseLegPart::PostLoad()
{
	Super::PostLoad();
	if (!Archetypes.IsEmpty())
	{
		for (UBaseArchetype* Archetype : Archetypes)
		{
			Archetype->RegisterLegPart(this);
		}
	}
}
