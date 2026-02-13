// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QuestLibrary.generated.h"

class UQuestData;

/**
 * 
 */

struct FQuestStage;
struct FQuest;

USTRUCT(BlueprintType)
struct FQuestObjective
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText Description;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	uint8 Quantity;

	uint8 TimesCompleted = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UQuestData> QuestData;

	FQuestStage* ParentStage;
	
};

USTRUCT(BlueprintType)
struct FQuestStage
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText StageName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText Description;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FQuestObjective> Objectives;

	FQuest* ParentQuest;

	FQuestStage* NextStage;

	bool bIsCompleted = false;
	
};

USTRUCT(BlueprintType)
struct FQuest : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText QuestName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FQuestStage> Stages;

	bool bIsCompleted = false;

	FQuest* NextQuest;
	
};

UCLASS()
class QUESTSYSTEM_API UQuestLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void StartQuestAt(UQuestData* QuestToStart, UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FText GetParentQuestName(UQuestData* Quest);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FText GetQuestDisplayName(UQuestData* QuestData);

	
};
