// Fill out your copyright notice in the Description page of Project Settings.


#include "HackableTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include <EnhancedInputComponent.h>
#include <Damageable.h>

AHackableTurret::AHackableTurret() {
	PrimaryActorTick.bCanEverTick = true;
	MouseInput = FVector2D::ZeroVector;

	DamageSystem = CreateDefaultSubobject<UDamageSystem>(TEXT("DamageSystem"));

	TurretBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretBase"));
	TurretBase->SetupAttachment(Root);

	TurretBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretBody"));
	TurretBody->SetupAttachment(TurretBase);

	TurretBarrel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretBarrel"));
	TurretBarrel->SetupAttachment(TurretBody);

}

void AHackableTurret::BeginPlay() {
	Super::BeginPlay();

	EnableInput(GetWorld()->GetFirstPlayerController());
}

void AHackableTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHackableTurret::OnCameraLookTriggered);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Completed, this, &AHackableTurret::OnCameraLookCompleted);
		EnhancedInput->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AHackableTurret::OnShootTriggered);
		EnhancedInput->BindAction(ShootAction, ETriggerEvent::Completed, this, &AHackableTurret::OnShootCompleted);
	}
}

void AHackableTurret::OnCameraLookTriggered(const FInputActionValue& Value)
{
	CameraLogic(Value);
}

void AHackableTurret::OnCameraLookCompleted(const FInputActionValue& Value) {
	CameraLogic(Value);
}

void AHackableTurret::OnShootTriggered(const FInputActionValue& Value) {
	if (!bHolding) {
		bHolding = true;
		GetWorldTimerManager().SetTimer(
			FireRateTimer,
			this,
			&AHackableTurret::ShootLogic,
			0.1f,
			true
		);
	}
}

void AHackableTurret::ShootLogic() {
	if (!bHolding) return;

    UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation(), 1.0f, 1.0f, 0.0f);

    FVector Start = TurretBody->GetComponentLocation();
    FVector ForwardVector = TurretBody->GetForwardVector();
    FVector End = Start + (ForwardVector * 25000);

    FHitResult HitResult;
    FCollisionQueryParams TraceParams(FName(TEXT("Trace")), true, this);
    TraceParams.bTraceComplex = true;
    TraceParams.bReturnPhysicalMaterial = false;

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, TraceParams);
    int32 RandValue = FMath::RandRange(2, 5);

	FColor LineColor = bHit ? FColor::Red : FColor::Green;
	DrawDebugLine(GetWorld(), Start, End, LineColor, false, 2.0f, 0, 5.0f);

	FDamageInfo DamageInfo;

	DamageInfo.Amount = 25.0f;
	DamageInfo.DamageType = EDamageTransmitter::Projectile;
	DamageInfo.DamageResponse = EDamageResponse::None;
	DamageInfo.ShouldDamageInvincible = false;
	DamageInfo.CanBeBlocked = true;
	DamageInfo.CanBeParried = true;
	DamageInfo.ShouldForceInterrupt = true;

    if (bHit) {
		AActor* HitActor = HitResult.GetActor();
		if (HitActor->GetClass()->ImplementsInterface(UDamageable::StaticClass())) {
			HitActor->GetComponentByClass<UDamageSystem>()->TakeDamage(DamageInfo, this);
		}
		else {

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.Location, FRotationMatrix::MakeFromX(HitResult.Normal).Rotator());
			UDecalComponent* DecalComp = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), ImpactDecal, FVector(RandValue), HitResult.Location, FRotationMatrix::MakeFromX(HitResult.Normal).Rotator(), 20);
		}
    }

	if (bHolding) {
		GetWorldTimerManager().SetTimer(
			FireRateTimer,
			this,
			&AHackableTurret::ShootLogic,
			0.1f,
			false
		);
	}
}

void AHackableTurret::OnShootCompleted(const FInputActionValue& Value) {
	GetWorldTimerManager().SetTimer(
		ShootCompletedTimer,
		this,
		&AHackableTurret::ResetDoOnce,
		0.15f,
		false
	);
}

void AHackableTurret::CameraLogic(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();

	MouseInput = InputVector;
}

void AHackableTurret::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!TurretBody) return;

	FRotator CurrentRot = TurretBody->GetRelativeRotation();

	CurrentRot.Yaw += MouseInput.X;
	CurrentRot.Pitch = FMath::Clamp(CurrentRot.Pitch + MouseInput.Y * 1.0f, -45.f, 45.f);

	TurretBody->SetRelativeRotation(CurrentRot);
}

void AHackableTurret::ResetDoOnce() {
	bHolding = false;

	GetWorldTimerManager().ClearTimer(ShootCompletedTimer);
}