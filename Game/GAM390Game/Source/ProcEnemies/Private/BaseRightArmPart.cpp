// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRightArmPart.h"
#include "BaseArchetype.h"
#include "Pawns/BaseProcEnemy.h"

void ABaseRightArmPart::AttatchPart(ABaseProcEnemy* Enemy)
{
	ABaseRightArmPart* Part = Cast<ABaseRightArmPart>(Enemy->GetWorld()->SpawnActor(GetClass()));
	Enemy->SetRightArm(Part);
	const FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);

	Part->AttachToComponent(Enemy->GetMeshComp(), Rules, Enemy->GetRightArmSocketName());
}

void ABaseRightArmPart::RemoveFromAllOldArchetypes()
{
	if (!OldArchetypes.IsEmpty())
	{
		for (UBaseArchetype* Archetype : OldArchetypes)
		{
			if (Archetype)
			{
				Archetype->RemoveFromRightArm(GetClass());
			}
		}
	}
}

void ABaseRightArmPart::AddToAllCurrentArchetypes()
{
	if (!Archetypes.IsEmpty())
	{
		for (UBaseArchetype* Archetype : Archetypes)
		{
			if (Archetype)
			{
				Archetype->RegisterRightArmPart(GetClass());
			}
		}
	}
}
