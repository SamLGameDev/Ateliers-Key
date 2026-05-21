// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLeftArmPart.h"
#include "BaseArchetype.h"
#include "Pawns/BaseProcEnemy.h"

void ABaseLeftArmPart::AttatchPart(ABaseProcEnemy* Enemy)
{
	ABaseLeftArmPart* Part = Cast<ABaseLeftArmPart>(Enemy->GetWorld()->SpawnActor(GetClass()));
	Enemy->SetLeftArm(Part);
	const FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);

	Part->AttachToComponent(Enemy->GetMeshComp(), Rules, Enemy->GetLeftArmSocketName());
}

void ABaseLeftArmPart::RemoveFromAllOldArchetypes()
{
	if (!OldArchetypes.IsEmpty())
	{
		for (UBaseArchetype* Archetype : OldArchetypes)
		{
			if (Archetype)
			{
				Archetype->RemoveFromLeftArm(GetClass());
			}

		}
	}
}

void ABaseLeftArmPart::AddToAllCurrentArchetypes()
{
	if (!Archetypes.IsEmpty())
	{
		for (UBaseArchetype* Archetype : Archetypes)
		{
			if(Archetype)
			{
				Archetype->RegisterLeftArmPart(GetClass());
			}

		}
	}
}
