// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Follow_Player.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

UBTT_Follow_Player::UBTT_Follow_Player() {
	NodeName = TEXT("Move To Player Offset");
}

EBTNodeResult::Type UBTT_Follow_Player::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();

	if (!BB) return EBTNodeResult::Failed;

	ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(OwnerComp.GetWorld(), 0);

	if (!PlayerChar) return EBTNodeResult::Failed;

	const FVector PlayerLocation = PlayerChar->GetActorLocation();
	const FVector RightVector = PlayerChar->GetActorRightVector();
	const FVector ForwardVector = PlayerChar->GetActorForwardVector();

	FVector DesiredLocation = PlayerLocation + (RightVector * RightOffset) + (ForwardVector * ForwardOffset);

	if (const UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld())) {
		FNavLocation ProjectedLocation;

		if (NavSys->ProjectPointToNavigation(DesiredLocation, ProjectedLocation)) {
			DesiredLocation = ProjectedLocation.Location;
		}
	}

	BB->SetValueAsVector(TEXT("FriendlyMoveLocation"), DesiredLocation);

	return EBTNodeResult::Succeeded;
}