// Fill out your copyright notice in the Description page of Project Settings.


#include "InputTriggerInitialDelayPulse.h"

ETriggerState UInputTriggerInitialDelayPulse::UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime)
{
	ETriggerState State = Super::UpdateState_Implementation(PlayerInput, ModifiedValue, DeltaTime);

	if (State == ETriggerState::Ongoing)
	{
		// If the repeat count limit has not been reached
		if (TriggerLimit == 0 || TriggerCount < TriggerLimit)
		{
			// Trigger when HeldDuration exceeds the interval threshold, optionally trigger on initial actuation, and Exceeds the initial delay
			if (HeldDuration - InitialDelay > (Interval * (bTriggerOnStart ? TriggerCount : TriggerCount + 1)) && HeldDuration > InitialDelay)
			{
				++TriggerCount;
				State = ETriggerState::Triggered;
			}
		}
		else
		{
			State = ETriggerState::None;
		}
	}
	else
	{
		// Reset repeat count
		TriggerCount = 0;
	}

	return State;
}
