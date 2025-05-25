// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLeftArmPart.h"
#include "BaseArchetype.h"
#include "Pawns/BaseProcEnemy.h"

void ABaseLeftArmPart::AttatchPart(ABaseProcEnemy* Enemy)
{
	Enemy->SetLeftArm(this);
	const FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);

	AttachToActor(Enemy, Rules, Enemy->GetHeadSocketName());
}

void ABaseLeftArmPart::PostLoad()
{
	Super::PostLoad();
	if (!Archetypes.IsEmpty())
	{
		for (UBaseArchetype* Archetype : Archetypes)
		{
			Archetype->RegisterLeftArmPart(this);
		}
	}
}
