// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBodyPart.h"
#include "BaseArchetype.h"
#include "Pawns/BaseProcEnemy.h"

ABaseBodyPart::ABaseBodyPart()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	Mesh->SetupAttachment(Root);
}

void ABaseBodyPart::ExecuteAbility()
{

}

void ABaseBodyPart::TakeDamage_Implementation(const int Damage)
{
	CurrentDurability -= Damage;
	if (CurrentDurability < 0)
	{
		Destroy();
	}

}

#if WITH_EDITOR
void ABaseBodyPart::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName propertyName = PropertyChangedEvent.GetPropertyName();

	if (propertyName == GET_MEMBER_NAME_CHECKED(ABaseBodyPart, Archetypes)) 
	{
		RemoveFromAllOldArchetypes();
		AddToAllCurrentArchetypes();
		OldArchetypes = Archetypes;
	}

}
#endif

void ABaseBodyPart::Destroy()
{
	const FDetachmentTransformRules Rules = FDetachmentTransformRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepRelative, false);
	DetachFromActor(Rules);
}
