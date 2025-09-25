// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HackableEnemy.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Camera/CameraComponent.h"
#include <DamageSystem.h>
#include <GUI_TurretHud.h>
#include "HackableTurret.generated.h"

/**
 * 
 */
UCLASS()
class HACKING_API AHackableTurret : public AHackableEnemy
{
	GENERATED_BODY()

public:
	AHackableTurret();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void StartCountdown();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret|Components")
	UDamageSystem* DamageSystem;

private:
	FTimerHandle ShootCompletedTimer;
	FTimerHandle FireRateTimer;
	FTimerHandle CountdownTimer;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* TurretBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* TurretBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* TurretBarrel;

	UPROPERTY(EditAnywhere, Category = "Turret|Rotation")
	float MinYaw = -90.f;

	UPROPERTY(EditAnywhere, Category = "Turret|Rotation")
	float MaxYaw = 90.f;

	UPROPERTY(EditAnywhere, Category = "Turret|Rotation")
	float MinPitch = -45.f;

	UPROPERTY(EditAnywhere, Category = "Turret|Rotation")
	float MaxPitch = 45.f;

	UPROPERTY(EditDefaultsOnly, Category = "Turret|Inputs")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Turret|Inputs")
	UInputAction* ShootAction;

	UPROPERTY(BlueprintReadWrite, Category = "Turret|Turret")
	FVector2D MouseInput;

	UPROPERTY(BlueprintReadWrite, Category = "Turret|Turret")
	bool bHolding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret|Effects")
	UNiagaraSystem* ImpactEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret|Effects")
	UMaterialInterface* ImpactDecal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret|Barrels")
	FName MuzzleSocketNameL = "Muzzle_L";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret|Barrels")
	FName MuzzleSocketNameR = "Muzzle_R";

	bool bLeftBarrel;

	UPROPERTY(BlueprintReadWrite, Category = "Turret|Damage System")
	int teamNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret|Damage System")
	int maxBulletCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret|Widget")
	TSubclassOf<UUserWidget> TurretHudWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret|Components")
	TSubclassOf<APawn> Actor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret|Audio")
	USoundBase* Sound;

	float currentBulletCount;

	UGUI_TurretHud* TurretHud;

	void OnCameraLookTriggered(const FInputActionValue& Value);
	void OnCameraLookCompleted(const FInputActionValue& Value);

	void OnShootTriggered(const FInputActionValue& Value);
	void OnShootCompleted(const FInputActionValue& Value);

	void CameraLogic(const FInputActionValue& Value);
	void ResetDoOnce();

	UFUNCTION(BlueprintCallable)
	void ShootLogicAI();

	UFUNCTION(BlueprintCallable)
	void ResetLogicAI();

	void ShootLogic();

	void CountdownComplete();
};
