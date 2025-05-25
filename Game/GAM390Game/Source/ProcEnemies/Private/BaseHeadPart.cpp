// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHeadPart.h"
#include "BaseArchetype.h"
#include "Pawns/BaseProcEnemy.h"

void ABaseHeadPart::AttatchPart(ABaseProcEnemy* Enemy)
{
	Enemy->SetHead(this);
	const FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);

	AttachToActor(Enemy, Rules, Enemy->GetHeadSocketName());
}

void ABaseHeadPart::PostLoad()
{
	Super::PostLoad();
	if (!Archetypes.IsEmpty())
	{
		for (UBaseArchetype* Archetype : Archetypes)
		{
			Archetype->RegisterHeadPart(this);
		}
	}
}

