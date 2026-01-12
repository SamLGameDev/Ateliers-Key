// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "Puppetry.generated.h"


/**
 * 
 */

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ABILITYSYSTEM_API UPuppetry : public UAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void StartExecution(AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void CancelExecution(const uint8& OriginalTeam, AActor* Puppet);
private:

	UPROPERTY(EditDefaultsOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
	uint8 PuppetTeam = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
	float PuppetDuration = 5;
	
};
