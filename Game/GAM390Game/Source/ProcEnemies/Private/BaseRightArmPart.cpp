// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRightArmPart.h"
#include "BaseArchetype.h"
#include "Pawns/BaseProcEnemy.h"

void ABaseRightArmPart::AttatchPart(ABaseProcEnemy* Enemy)
{
	Enemy->SetRightArm(this);
	const FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);

	AttachToActor(Enemy, Rules, Enemy->GetHeadSocketName());
}

void ABaseRightArmPart::PostLoad()
{
	Super::PostLoad();
	if (!Archetypes.IsEmpty())
	{
		for (UBaseArchetype* Archetype : Archetypes)
		{
			Archetype->RegisterRightArmPart(this);
		}
	}
}
