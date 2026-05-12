// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Puppetry.h"

#include "Damageable.h"

void UPuppetry::StartExecution(AActor* Target)
{
	if (Target->Implements<UDamageable>())
	{
		int32 originalTeamNumber;
		IDamageable::Execute_GetTeamNumber(Target, originalTeamNumber);
		IDamageable::Execute_SetTeamNumber(Target, PuppetTeam);
		TArray<USkeletalMeshComponent*> SkeletalMeshComponents;
		Target->GetComponents<USkeletalMeshComponent>(SkeletalMeshComponents);
		TargetMesh = nullptr;
		for (auto& SkeletalMeshComponent : SkeletalMeshComponents)
		{
			if (SkeletalMeshComponent->ComponentHasTag("Body"))
			{
				TargetMesh = SkeletalMeshComponent;
				break;
			}
		}
	
		checkf(TargetMesh, TEXT("Found no mesh for Puppetry with tag Body"));
	
		TargetMesh->SetOverlayMaterial(OverlayMat);
		FTimerDelegate puppetDelegate;
		puppetDelegate.BindUFunction(this, "CancelExecution", originalTeamNumber, Target);
		FTimerHandle puppetTimer;
		GetWorld()->GetTimerManager().SetTimer(puppetTimer, puppetDelegate, PuppetDuration, false);
	}
}

void UPuppetry::CancelExecution(const uint8& OriginalTeam, AActor* Puppet)
{
	if (!Puppet) return;
	IDamageable::Execute_SetTeamNumber(Puppet, OriginalTeam);
	TargetMesh->SetOverlayMaterial(nullptr);
}

