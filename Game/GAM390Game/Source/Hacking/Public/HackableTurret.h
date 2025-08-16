// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HackableEnemy.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include <DamageSystem.h>
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

private:
	FTimerHandle ShootCompletedTimer;
	FTimerHandle FireRateTimer;
	FTimerHandle CountdownTimer;


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* TurretBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* TurretBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* TurretBarrel;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	UInputAction* ShootAction;

	UPROPERTY(BlueprintReadWrite, Category = "Turret")
	FVector2D MouseInput;

	UPROPERTY(BlueprintReadWrite, Category = "Turret")
	bool bHolding;

	UPROPERTY(BlueprintReadWrite, Category = "Turret")
	int teamNumber;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDamageSystem* DamageSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TSubclassOf<APawn> Actor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UMaterialInterface* ImpactDecal;

	void OnCameraLookTriggered(const FInputActionValue& Value);
	void OnCameraLookCompleted(const FInputActionValue& Value);

	void OnShootTriggered(const FInputActionValue& Value);
	void OnShootCompleted(const FInputActionValue& Value);

	void CameraLogic(const FInputActionValue& Value);
	void ResetDoOnce();

	void ShootLogic();

	void CountdownComplete();

};
