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

	UFUNCTION(BlueprintCallable)
	void Heal(float amount);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(const FDamageInfo& DamageInfo, AActor* Source);

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

protected:
	static void CallOnDeath(AActor* DamagedActor);

	void CallOnDamageResponse(const FDamageInfo& DamageResponse);
		
};
