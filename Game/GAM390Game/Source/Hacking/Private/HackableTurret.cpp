// Fill out your copyright notice in the Description page of Project Settings.


#include "HackableTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/DecalComponent.h"
#include <EnhancedInputComponent.h>
#include <Damageable.h>

AHackableTurret::AHackableTurret() {
	PrimaryActorTick.bCanEverTick = true;
	MouseInput = FVector2D::ZeroVector;

	DamageSystem = CreateDefaultSubobject<UDamageSystem>(TEXT("DamageSystem"));

	TurretBase = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TurretBase"));
	TurretBase->SetupAttachment(Root);

	TurretBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretBody"));
	TurretBody->SetupAttachment(TurretBase);

	TurretBarrel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TurretBarrel"));
	TurretBarrel->SetupAttachment(TurretBody);

}

void AHackableTurret::BeginPlay() {
	Super::BeginPlay();

	EnableInput(GetWorld()->GetFirstPlayerController());

	currentBulletCount = maxBulletCount;
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

void AHackableTurret::ShootLogicAI() {
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

void AHackableTurret::ResetLogicAI() {
	GetWorldTimerManager().SetTimer(
		ShootCompletedTimer,
		this,
		&AHackableTurret::ResetDoOnce,
		0.15f,
		false
	);
}

void AHackableTurret::ShootLogic() {
	if (!bHolding || currentBulletCount <= 0) return;

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation(), 1.0f, 1.0f, 0.0f);

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC) return;

	int32 ViewportX, ViewportY;
	PC->GetViewportSize(ViewportX, ViewportY);
	FVector WorldLocation, WorldDirection;
	PC->DeprojectScreenPositionToWorld(ViewportX * 0.5f, ViewportY * 0.5f, WorldLocation, WorldDirection);

	FVector TargetEnd = WorldLocation + (WorldDirection * 25000.f);

	FHitResult CameraHit;
	FCollisionQueryParams CameraTraceParams(FName(TEXT("CameraTrace")), true, this);
	CameraTraceParams.bTraceComplex = true;

	bool bCameraHit = GetWorld()->LineTraceSingleByChannel(
		CameraHit, WorldLocation, TargetEnd, ECC_Visibility, CameraTraceParams
	);

	FVector FinalTarget = bCameraHit ? CameraHit.Location : TargetEnd;

	FName SocketName = bLeftBarrel ? MuzzleSocketNameL : MuzzleSocketNameR;
	bLeftBarrel = !bLeftBarrel;

	if (!TurretBarrel || !TurretBarrel->DoesSocketExist(SocketName)) return;

	FVector Start = TurretBarrel->GetSocketLocation(SocketName);
	FVector End = FinalTarget;

	FHitResult HitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("TurretTrace")), true, this);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = false;

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, TraceParams);

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
		if (HitActor && HitActor->GetClass()->ImplementsInterface(UDamageable::StaticClass())) {
			if (UDamageSystem* DS = HitActor->GetComponentByClass<UDamageSystem>()) {
				DS->TakeDamage(DamageInfo, this);
			}
		}
		else {
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactEffect, HitResult.Location, FRotationMatrix::MakeFromX(HitResult.Normal).Rotator());

			float LifeSpan = 10.f;
			float FadeScreenSize = 0.001f;

			int32 RandValue = FMath::RandRange(2, 5);
			UDecalComponent* DecalComp = UGameplayStatics::SpawnDecalAtLocation(
				GetWorld(), ImpactDecal, FVector(RandValue),
				HitResult.Location,
				FRotationMatrix::MakeFromX(HitResult.Normal).Rotator(),
				LifeSpan
			);

			if (DecalComp) {
				DecalComp->FadeScreenSize = FadeScreenSize;
				DecalComp->SetFadeScreenSize(FadeScreenSize);
			}
		}
	}

	currentBulletCount--;
	if (TurretHud) TurretHud->UpdateBulletCount(currentBulletCount, maxBulletCount);

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

	if (!TurretBody || !TurretBarrel) return;

	FRotator BodyRot = TurretBody->GetRelativeRotation();
	BodyRot.Yaw += MouseInput.X;
	TurretBody->SetRelativeRotation(BodyRot);

	FRotator BarrelRot = TurretBarrel->GetRelativeRotation();
	BarrelRot.Roll = FMath::Clamp(BarrelRot.Roll - MouseInput.Y, -45.f, 45.f);
	TurretBarrel->SetRelativeRotation(BarrelRot);
}


void AHackableTurret::ResetDoOnce() {
	bHolding = false;

	GetWorldTimerManager().ClearTimer(ShootCompletedTimer);
}

void AHackableTurret::StartCountdown() {

	if (TurretHudWidgetClass)
	{
		TurretHud = CreateWidget<UGUI_TurretHud>(GetWorld(), TurretHudWidgetClass);
		if (TurretHud)
		{
			TurretHud->AddToViewport();
			TurretHud->turret = this;
			TurretHud->UpdateBulletCount(currentBulletCount, maxBulletCount);
		}
	}

	GetWorldTimerManager().SetTimer(
		CountdownTimer,
		this,
		&AHackableTurret::CountdownComplete,
		5.0f,
		false
	);
}

void AHackableTurret::CountdownComplete()
{
	GetWorldTimerManager().ClearTimer(CountdownTimer);

	if (!Actor) return;

	UWorld* World = GetWorld();
	if (!World) return;

	APawn* FoundPawn = Cast<APawn>(UGameplayStatics::GetActorOfClass(World, Actor));
	if (!FoundPawn)
	{
		return;
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
	if (!PC) return;

	PC->Possess(FoundPawn);

	MouseInput = FVector2D::ZeroVector;

	ResetDoOnce();

	TurretHud->RemoveFromViewport();
}