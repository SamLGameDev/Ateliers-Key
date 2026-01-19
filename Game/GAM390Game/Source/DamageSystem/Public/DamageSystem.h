// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "DamageInfo.h"
#include "DamageSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBlocked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamageResponse, EDamageResponse, DamageResponse, AActor*, Source);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAMAGESYSTEM_API UDamageSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category = "Damage")
	FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable, Category = "Damage")
	FOnBlocked OnBlocked;

	UPROPERTY(BlueprintAssignable, Category = "Damage")
	FOnDamageResponse OnDamageResponse;

	UPROPERTY(BlueprintAssignable, Category = "Damage")
	FOnDamageResponse OnCriticalThreasholdReached;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 AttackTokensCount;

	UFUNCTION(BlueprintCallable)
	void Heal(float Amount);

	UFUNCTION(BlueprintCallable)
	void HealTemp(float Amount);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(const FDamageInfo& DamageInfo, AActor* Source);

	UFUNCTION(BlueprintCallable)
	bool ReserveAttackToken(int32 Amount);

	UFUNCTION(BlueprintCallable)
	void ReturnAttackToken(int32 Amount);

	UFUNCTION(BlueprintCallable)
	void ResetHealth();

	UFUNCTION(BlueprintCallable)
	void CompleteReset();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool IsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool IsInvincible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool IsBlocking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentTempHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxTempHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
	int TeamNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float HeadshotDamageMultiplier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float CriticalHealthThreashold = 0;

protected:
	static void CallOnDeath(AActor* DamagedActor);

	void CallOnDamageResponse(const FDamageInfo& DamageResponse);
		
};
