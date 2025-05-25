// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTorsoPart.h"
#include "BaseArchetype.h"
#include "Pawns/BaseProcEnemy.h"

void ABaseTorsoPart::AttatchPart(ABaseProcEnemy* Enemy)
{
	Enemy->SetTorso(this);
	const FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);

	AttachToActor(Enemy, Rules, Enemy->GetHeadSocketName());
}

void ABaseTorsoPart::PostLoad()
{
	Super::PostLoad();
	if (!Archetypes.IsEmpty())
	{
		for (UBaseArchetype* Archetype : Archetypes)
		{
			Archetype->RegisterTorsoPart(this);
		}
	}
}
