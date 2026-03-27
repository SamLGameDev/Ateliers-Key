// Fill out your copyright notice in the Description page of Project Settings.


#include "Notification.h"

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

void UNotification::BindToNotification(FOnNotifBind event)
{
	if (IsComplete())
	{
		event.Execute();
		return;
	}
	OnAllConditionsPassed.Add(event);
}

bool UNotification::IsComplete()
{
	for (const auto& condition : Conditions)
	{
		if (!condition) continue;
		if (!condition->IsComplete()) return false;
	}
	return true;
}

void UNotification::EvaluateConditions()
{
	for (const auto& condition : Conditions)
	{
		if (!condition) continue;
		
		if (!condition->IsComplete()) return;
	}
	
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
		const FString PackageName = package->GetName();
		const FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
		FSavePackageArgs args;
		//GEditor->SavePackage(package, Condition.Get(), GetData(package->GetName()), args);
		package->Save(package, Condition.Get(), *PackageFileName, args);
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
