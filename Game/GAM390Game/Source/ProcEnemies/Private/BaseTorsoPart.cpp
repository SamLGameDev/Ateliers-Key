// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTorsoPart.h"
#include "BaseArchetype.h"
#include "Pawns/BaseProcEnemy.h"

void ABaseTorsoPart::AttatchPart(ABaseProcEnemy* Enemy)
{
	ABaseTorsoPart* Part = Cast<ABaseTorsoPart>(Enemy->GetWorld()->SpawnActor(GetClass()));
	Enemy->SetTorso(Part);
	const FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);

	Part->AttachToComponent(Enemy->GetMeshComp(), Rules, Enemy->GetTorsoSocketName());
}

void ABaseTorsoPart::RemoveFromAllOldArchetypes()
{
	if (!OldArchetypes.IsEmpty())
	{
		for (UBaseArchetype* Archetype : OldArchetypes)
		{
			if (Archetype)
			{
				Archetype->RemoveFromTorso(GetClass());
			}
		}
	}
}

void ABaseTorsoPart::AddToAllCurrentArchetypes()
{
	if (!Archetypes.IsEmpty())
	{
		for (UBaseArchetype* Archetype : Archetypes)
		{
			if (Archetype)
			{
				Archetype->RegisterTorsoPart(GetClass());
			}
		}
	}
}
