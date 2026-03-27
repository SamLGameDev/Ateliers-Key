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
	
	DECLARE_DYNAMIC_DELEGATE(FOnNotifBind);
	
public:
	
	FOnConditionPassed OnConditionPassed;
	
	UPROPERTY(BlueprintAssignable )
	FOnAllConditionsPassed OnAllConditionsPassed;
	
	UFUNCTION(BlueprintCallable)
	void BindToNotification(FOnNotifBind event);
	
	UFUNCTION(BlueprintCallable)
	bool IsComplete();

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
