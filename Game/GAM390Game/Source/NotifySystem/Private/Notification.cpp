// Fill out your copyright notice in the Description page of Project Settings.


#include "Notification.h"

#include "FileHelpers.h"
#include "NotifyCondition.h"
#include "UObject/SavePackage.h"

UNotification::UNotification(const FObjectInitializer& Initializer)
{
	OnConditionPassed.AddDynamic(this, &UNotification::EvaluateConditions);
	
	for (const auto& Condition : Conditions)
	{
		if (!Condition) continue;
		Condition->AddNotification(this);
	}
}

void UNotification::EvaluateConditions()
{
	for (const auto& condition : Conditions)
	{
		if (!condition) continue;
		
		if (!condition->IsComplete()) return;
	}
	if (OnAllConditionsPassed.IsBound()) UE_LOG(LogTemp, Warning, TEXT("Conditions have been changed"));
	
	OnAllConditionsPassed.Broadcast();
}

#if WITH_EDITOR

void UNotification::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	
	for (auto& Condition : Conditions)
	{
		if (!Condition) continue;
		Condition->AddNotification(this);
		
		UPackage* package = Condition->GetOutermost();
		package->MarkPackageDirty();
		FSavePackageArgs args;
		package->Save(package, Condition.Get(), GetData(package->GetName()), args);
	}
	
}

void UNotification::PreEditChange(FProperty* PropertyAboutToChange)
{
	Super::PreEditChange(PropertyAboutToChange);
	for (const auto& Condition : Conditions)
	{
		if (!Condition) continue;
		Condition->RemoveNotification(this);
	}
}
#endif
