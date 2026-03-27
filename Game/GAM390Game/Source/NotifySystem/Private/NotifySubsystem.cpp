// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifySubsystem.h"

#include "Notification.h"
#include "NotifyCondition.h"
#include "Engine/AssetManager.h"

void UNotifySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	TArray<FAssetData> ConditionDataAssets;

	FARFilter Filter;
	Filter.ClassPaths.Add(UNotifyCondition::StaticClass()->GetClassPathName());

	FAssetRegistryModule::GetRegistry().GetAssets(Filter, ConditionDataAssets);
	
	for (auto& data : ConditionDataAssets)
	{
		UNotifyCondition* condition = Cast<UNotifyCondition>(data.GetAsset());
		condition->MarkUnComplete();
	}
	
}
