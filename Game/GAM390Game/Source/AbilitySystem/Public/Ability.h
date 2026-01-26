// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ability.generated.h"

UENUM(BlueprintType)
enum class ECancelPriority : uint8
{
	Absolute UMETA(DisplayName = "Absolute"),
	Normal   UMETA(DisplayName = "Normal")
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ABILITYSYSTEM_API UAbility : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAbility();

	virtual void StartExecution() PURE_VIRTUAL(UAbility::StartExecution);

	virtual void CancelExecution() PURE_VIRTUAL(UAbility::CancelExecution);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability")
	bool bIsUnlocked;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
