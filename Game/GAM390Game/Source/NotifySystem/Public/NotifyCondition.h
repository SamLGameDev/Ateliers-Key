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
class NOTIFYSYSTEM_API UNotifyCondition : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	
	void AddNotification(UNotification* Notification);
	void RemoveNotification(UNotification* Notification);
	
	
	UFUNCTION(BlueprintCallable)
	void Complete();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsComplete()
	{
		return bPassed;
	}
	
protected:
	UPROPERTY(VisibleAnywhere, NonPIEDuplicateTransient)
	
	TArray<TSoftObjectPtr<UNotification>> Notifications;
		
	bool bPassed = false;
};
