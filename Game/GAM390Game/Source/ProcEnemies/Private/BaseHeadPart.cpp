// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHeadPart.h"
#include "BaseArchetype.h"
#include "Pawns/BaseProcEnemy.h"

void ABaseHeadPart::AttatchPart(ABaseProcEnemy* Enemy)
{
	ABaseHeadPart* Part = Cast<ABaseHeadPart>(Enemy->GetWorld()->SpawnActor(GetClass()));
	Enemy->SetHead(Part);
	const FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);

	Part->AttachToComponent(Enemy->GetMeshComp(), Rules, Enemy->GetHeadSocketName());
}

void ABaseHeadPart::RemoveFromAllOldArchetypes()
{
	if (!OldArchetypes.IsEmpty())
	{
		for (UBaseArchetype* Archetype : OldArchetypes)
		{
			if (Archetype)
			{
				Archetype->RemoveFromHead(GetClass());
			}
		}
	}
}

void ABaseHeadPart::AddToAllCurrentArchetypes()
{
	if (!Archetypes.IsEmpty())
	{
		for (UBaseArchetype* Archetype : Archetypes)
		{
			if (Archetype)
			{
				Archetype->RegisterHeadPart(GetClass());
			}
		}
	}	
}

