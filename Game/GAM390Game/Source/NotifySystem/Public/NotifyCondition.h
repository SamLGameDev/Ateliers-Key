// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NotifyCondition.generated.h"

class UNotification;
/**
 * 
 */
UCLASS()
class NOTIFYSYSTEM_API UNotifyCondition : public UObject
{
	GENERATED_BODY()

public:

	UNotifyCondition();
	
	void AddNotification(UNotification* Notification);
	void RemoveNotification(UNotification* Notification);
	
	
	UFUNCTION(BlueprintCallable)
	void Complete();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsComplete()
	{
		return bPassed;
	}
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("NotifyCondition", NAME_None);
	}
	
	void MarkUnComplete();
	
protected:
	UPROPERTY(VisibleAnywhere, NonPIEDuplicateTransient)
	
	TArray<TSoftObjectPtr<UNotification>> Notifications;
	
	UPROPERTY(VisibleAnywhere, Transient)
	bool bPassed = false;
};
