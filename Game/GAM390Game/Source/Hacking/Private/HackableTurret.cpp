// Fill out your copyright notice in the Description page of Project Settings.


#include "HackableTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include <EnhancedInputComponent.h>

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
	bHolding = true;
	if (bHolding) {
		ShootLogic();
	}
}

void AHackableTurret::ShootLogic() {
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation(), 1.0f, 1.0f, 0.0f);

	FVector Start = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector End = Start + (ForwardVector * 25000);

	FHitResult HitResult;

	FCollisionQueryParams TraceParams(FName(TEXT("Trace")), true, this);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = false;

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, TraceParams);
	int32 RandValue = FMath::RandRange(2, 5);

	if (bHit) {
		/*HitResult.GetActor()->Implements*/
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, HitResult.Location, FRotationMatrix::MakeFromX(HitResult.Normal).Rotator());
		UDecalComponent* DecalComp = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), ImpactDecal, FVector(RandValue, RandValue, RandValue), HitResult.Location, FRotationMatrix::MakeFromX(HitResult.Normal).Rotator(), 20);
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

void AHackableTurret::CameraLogic(const FInputActionValue& Value) {
	FVector2D InputVector = Value.Get<FVector2D>();
	MouseInput = InputVector;

	AddControllerPitchInput(MouseInput.Y * -1.0f);
	AddControllerYawInput(MouseInput.X);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Move"));
}

void AHackableTurret::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	FRotator ControlRot = GetControlRotation();

	// 2️⃣ Create a new rotator keeping only yaw
	FRotator NewRot(0.f, ControlRot.Yaw, 0.f);

	// 3️⃣ Set relative rotation of TurretBody
	TurretBody->SetRelativeRotation(NewRot);
}

void AHackableTurret::ResetDoOnce() {
	bHolding = true;
}