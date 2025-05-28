// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseArchetype.h"
#include "BaseBodyPart.h"
#include "BehaviorTree/BehaviorTree.h"

void UBaseArchetype::RegisterHeadPart(TSubclassOf<ABaseBodyPart> Part)
{
	HeadParts.Add(Part);
}

void UBaseArchetype::RegisterTorsoPart(TSubclassOf<ABaseBodyPart> Part)
{
	TorsoParts.Add(Part);
}

void UBaseArchetype::RegisterLegPart(TSubclassOf<ABaseBodyPart> Part)
{
	LegParts.Add(Part);
}

void UBaseArchetype::RegisterLeftArmPart(TSubclassOf<ABaseBodyPart> Part)
{
	LeftArmParts.Add(Part);
}

void UBaseArchetype::RegisterRightArmPart(TSubclassOf<ABaseBodyPart> Part)
{
	RightArmParts.Add(Part);
}

void UBaseArchetype::RemoveFromHead(TSubclassOf<ABaseBodyPart> Part)
{
	HeadParts.Remove(Part);
}

void UBaseArchetype::RemoveFromTorso(TSubclassOf<ABaseBodyPart> Part)
{
	TorsoParts.Remove(Part);
}

void UBaseArchetype::RemoveFromLeftArm(TSubclassOf<ABaseBodyPart> Part)
{
	LeftArmParts.Remove(Part);
}

void UBaseArchetype::RemoveFromRightArm(TSubclassOf<ABaseBodyPart> Part)
{
	RightArmParts.Remove(Part);
}

void UBaseArchetype::RemoveFromLegs(TSubclassOf<ABaseBodyPart> Part)
{
	LegParts.Remove(Part);
}
