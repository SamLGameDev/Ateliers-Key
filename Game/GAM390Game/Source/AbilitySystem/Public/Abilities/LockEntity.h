// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "InputMappingContext.h"
#include "LockEntity.generated.h"

class ABaseEnemyController;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ABILITYSYSTEM_API ULockEntity : public UAbility
{
	GENERATED_BODY()

public:

	void StartExecution() override {};

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void CancelExecution();

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void StartExecution(AActor* Target);


	UFUNCTION(BlueprintCallable, Category = "Ability")
	void StartPlayerLock(APawn* Player);

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	float Duration;

private:

	FTimerHandle EndLockHandle;

	ABaseEnemyController* TargetController;

	uint8 StopId;
		
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	UInputMappingContext* PlayerLockedMap;
	
	UPROPERTY()
	TObjectPtr<AActor> TargetForLock;
	
	UPROPERTY(EditAnywhere, Category = "Ability")
	UMaterial* OverlayMat;
	
	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> TargetMesh;
	
};
