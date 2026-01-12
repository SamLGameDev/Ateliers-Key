// CodeLikmeMe Menu System Copyright (C) 2025 CodeLikeMe GmbH

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DisplayInfo.h"
#include "ExtendedUserSettingSubsystem.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CLMMENUSYSTEM_API UExtendedUserSettingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "CLM Menu System|User Settings|Display")
	TArray<FDisplayInfo> GetAllFDisplayInfo() const;

	UFUNCTION(BlueprintCallable, Category = "CLM Menu System|User Settings|Display")
	void SetActiveDisplayById(const FString& DisplayId);
};
