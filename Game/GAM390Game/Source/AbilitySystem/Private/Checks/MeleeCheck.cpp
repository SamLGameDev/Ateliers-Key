// Fill out your copyright notice in the Description page of Project Settings.


#include "Checks/MeleeCheck.h"

static TAutoConsoleVariable<int32> CShowMeleeDebug(
	TEXT("MeleeDebug.show"),
	0,
	TEXT("Show my debug boxes: 0=off, 1=on"),
	ECVF_Default);

// Sets default values for this component's properties
UMeleeCheck::UMeleeCheck()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UMeleeCheck::DetectHitEntity(FHitResult& HitInfo) const
{
	const APawn* owner = Cast<APawn>(GetOwner());
	
	const FVector Start = GetOwner()->GetActorLocation();
	const FVector End = Start + Cast<APlayerController>(owner->GetController())->PlayerCameraManager->GetCameraRotation().Vector() * MeleeOffset;


	//Rotate it around the Z axis, so its facing the players direction, but not affecting the bounds
	const FQuat Rot = FRotator(0, owner->GetControlRotation().Yaw,0).Quaternion();

	FCollisionObjectQueryParams CollisionObjectParams;
	CollisionObjectParams.AddObjectTypesToQuery(ECC_Pawn);

	FCollisionShape CollisionBox = FCollisionShape::MakeBox(MeleeBoxHalfBounds);

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(owner);

	const bool bHit = GetWorld()->SweepSingleByObjectType
	(
		HitInfo,
		End,
		End,
		Rot,
		CollisionObjectParams,
		FCollisionShape::MakeBox(MeleeBoxHalfBounds),
		CollisionQueryParams
	);

	if (CShowMeleeDebug.GetValueOnAnyThread())
	{
		DrawDebugBox(GetWorld(), End, CollisionBox.GetExtent(),Rot, bHit ? FColor::Green : FColor::Red, false, 100, 1, 1);
	}

	return bHit;
}

bool UMeleeCheck::Check(FHitResult& Result) const
{
	const bool bHit = DetectHitEntity(Result);

	return bHit;
}


// Called when the game starts
void UMeleeCheck::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMeleeCheck::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

