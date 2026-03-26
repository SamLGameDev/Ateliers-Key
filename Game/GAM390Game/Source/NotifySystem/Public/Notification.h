// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Notification.generated.h"

class UNotifyCondition;
/**
 * 
 */
UCLASS()
class NOTIFYSYSTEM_API UNotification : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
	UNotification(const FObjectInitializer& Initializer);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConditionPassed);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllConditionsPassed);
	
public:
	
	FOnConditionPassed OnConditionPassed;
	
	UPROPERTY(BlueprintAssignable)
	FOnAllConditionsPassed OnAllConditionsPassed;

protected:
	
	UFUNCTION()
	void EvaluateConditions();
	
	UPROPERTY(EditAnywhere)
	TArray<TSoftObjectPtr<UNotifyCondition>> Conditions;
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
	
#endif
};
