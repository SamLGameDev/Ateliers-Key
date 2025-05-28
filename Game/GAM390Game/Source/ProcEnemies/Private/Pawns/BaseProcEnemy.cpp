// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BaseProcEnemy.h"
#include "Perception/PawnSensingComponent.h"
#include "BaseBodyPart.h"
#include "BaseArchetype.h"
#include "BaseLeftArmPart.h"
#include "BaseTorsoPart.h"
#include "BaseHeadPart.h"
#include "BaseLegPart.h"
#include "BaseRightArmPart.h"
#include "Controllers/BaseProcEnemyController.h"

// Sets default values
ABaseProcEnemy::ABaseProcEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	Sensor = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Sensor"));
}

void ABaseProcEnemy::SetHead(ABaseHeadPart* InHead)
{
	Head = InHead;
	
}

 //Called when the game starts or when spawned
void ABaseProcEnemy::BeginPlay()
{
	Super::BeginPlay();

	Archetype = Cast<UBaseArchetype>(Archetypes[FMath::RandRange(0, Archetypes.Num()-1)]);

	if (!Archetype->CheckCompleteBodyPossible())
	{
		return;
	}

	TArray<FCompleteBody> possibleParts;

	GetAllPossibleCombinationsOfParts(possibleParts, 0, 0, 0 ,0, 0);

	if (possibleParts.IsEmpty())
	{
		return;
	}

	FCompleteBody* Body = &possibleParts[FMath::RandRange(0, possibleParts.Num() - 1)];

	Body->Head->AttatchPart(this);
	Body->Torso->AttatchPart(this);
	Body->Legs->AttatchPart(this);
	Body->LeftArm->AttatchPart(this);
	Body->RightArm->AttatchPart(this);

	Cast<ABaseProcEnemyController>(GetController())->SetUp(Archetype->GetBehaviorTree());

}

void ABaseProcEnemy::GetAllPossibleCombinationsOfParts(TArray<FCompleteBody>& PossibleComs, int HeadIndex, int TorsoIndex, int LegsIndex, int LeftArmIndex, int RightArmIndex)
{
	ABaseBodyPart* head = Cast<ABaseBodyPart>(Archetype->GetHeadParts().Array()[HeadIndex].GetDefaultObject());
	ABaseBodyPart* torso = Cast<ABaseBodyPart>(Archetype->GetTorsoParts().Array()[TorsoIndex].GetDefaultObject());
	ABaseBodyPart* legs = Cast<ABaseBodyPart>(Archetype->GetLegParts().Array()[LegsIndex].GetDefaultObject());
	ABaseBodyPart* leftArm = Cast<ABaseBodyPart>(Archetype->GetLeftArmParts().Array()[LeftArmIndex].GetDefaultObject());
	ABaseBodyPart* rightArm = Cast<ABaseBodyPart>(Archetype->GetRightArmParts().Array()[RightArmIndex].GetDefaultObject());
	
	int cost = head->GetCost() + torso->GetCost() + legs->GetCost() + leftArm->GetCost() + rightArm->GetCost();

	if (FMath::IsWithinInclusive(cost, ThreatRange.X, ThreatRange.Y))
	{
		PossibleComs.Add(FCompleteBody(head, torso, legs, leftArm, rightArm));
	}

	RightArmIndex++;
	if (RightArmIndex == Archetype->GetRightArmParts().Num())
	{
		RightArmIndex = 0;
		LeftArmIndex++;
		if (LeftArmIndex == Archetype->GetLeftArmParts().Num())
		{
			LeftArmIndex = 0;
			LegsIndex++;
			if (LegsIndex == Archetype->GetLegParts().Num())
			{
				LegsIndex = 0;
				TorsoIndex++;
				if (TorsoIndex == Archetype->GetTorsoParts().Num())
				{
					TorsoIndex = 0;
					HeadIndex++;
					if (HeadIndex == Archetype->GetHeadParts().Num())
					{
						return;
					}
				}

			}
		}
	}

	GetAllPossibleCombinationsOfParts(PossibleComs, HeadIndex, TorsoIndex, LegsIndex, LeftArmIndex, RightArmIndex);

}

// Called every frame
void ABaseProcEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

