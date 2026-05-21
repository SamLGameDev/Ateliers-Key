// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLegPart.h"
#include "BaseArchetype.h"
#include "Pawns/BaseProcEnemy.h"

void ABaseLegPart::AttatchPart(ABaseProcEnemy* Enemy)
{
	ABaseLegPart* Part = Cast<ABaseLegPart>(Enemy->GetWorld()->SpawnActor(GetClass()));
	Enemy->SetLegs(Part);
	const FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);

	Part->AttachToComponent(Enemy->GetMeshComp(), Rules, Enemy->GetLegsSocketName());
}

void ABaseLegPart::RemoveFromAllOldArchetypes()
{
	if (!OldArchetypes.IsEmpty())
	{
		for (UBaseArchetype* Archetype : OldArchetypes)
		{
			if (Archetype)
			{
				Archetype->RemoveFromLegs(GetClass());
			}

		}
	}
}

void ABaseLegPart::AddToAllCurrentArchetypes()
{
	if (!Archetypes.IsEmpty())
	{
		for (UBaseArchetype* Archetype : Archetypes)
		{
			if (Archetype)
			{
				Archetype->RegisterLegPart(GetClass());
			}
		}
	}
}