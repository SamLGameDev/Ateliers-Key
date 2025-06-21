// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "InputTriggerInitialDelayPulse.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Initial Delay Pulse"))
class ENCHANCEDINPUTADDITIONS_API UInputTriggerInitialDelayPulse : public UInputTriggerTimedBase
{
	GENERATED_BODY()

private:

	int32 TriggerCount = 0;

protected:

	virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;

public:
	// Whether to trigger when the input first exceeds the actuation threshold or wait for the first interval?
	UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings")
	bool bTriggerOnStart = true;

	// How long between each trigger fire while input is held, in seconds?
	UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings", meta = (ClampMin = "0"))
	float Interval = 1.0f;

	//How long the Initial Delay should be
	UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings", meta = (ClampMin = "0"))
	float InitialDelay = 1.0f;

	// How many times can the trigger fire while input is held? (0 = no limit)
	UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings", meta = (ClampMin = "0"))
	int32 TriggerLimit = 0;

	virtual FString GetDebugState() const override { return HeldDuration ? FString::Printf(TEXT("Triggers:%d/%d, Interval:%.2f/%.2f"), TriggerCount, TriggerLimit, (HeldDuration / (Interval * (TriggerCount + 1))), Interval) : FString(); }
};
