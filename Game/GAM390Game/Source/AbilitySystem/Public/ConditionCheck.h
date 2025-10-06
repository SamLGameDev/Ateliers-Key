// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ConditionCheck.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ABILITYSYSTEM_API UConditionCheck : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UConditionCheck();

	UFUNCTION(BlueprintCallable, Category = "Ability")
	virtual bool CheckOld() PURE_VIRTUAL(UConditionCheck::Check, return false;);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
