// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "DamageInfo.h"
#include "DamageSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBlocked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHeal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamageResponse, EDamageResponse, DamageResponse, AActor*, Source);
DECLARE_DYNAMIC_DELEGATE_OneParam(FHealFunc, float, Amount);

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
	FOnHeal OnHeal;
	
	UPROPERTY(BlueprintAssignable, Category = "Damage")
	FOnHeal OnHealTemp;

	UPROPERTY(BlueprintAssignable, Category = "Damage")
	FOnDamageResponse OnDamageResponse;

	UPROPERTY(BlueprintAssignable, Category = "Damage")
	FOnDamageResponse OnCriticalThreasholdReached;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 AttackTokensCount;

	int32 MaxAttackTokens;

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
	
	UFUNCTION(BlueprintCallable)
	void StartHealthPerTick(const float& Amount, const float& Duration, uint8& ID, const bool& TempHealth);

	UFUNCTION()
	void HealTick(const float Duration, const float Amount, const uint8 ID, const FHealFunc& HealFunc);

	UFUNCTION()
	void CancelHealTick(const uint8& ID);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool IsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool IsInvincible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool IsBlocking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentTempHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxTempHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
	int TeamNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float HeadshotDamageMultiplier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float CriticalHealthThreashold = 0;

protected:
	static void CallOnDeath(AActor* DamagedActor);

	void CallOnDamageResponse(const FDamageInfo& DamageResponse);

	

	TMap<uint8, FTimerHandle> HealthPerTickHandles;
	
};
