// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QuestLibrary.generated.h"

class UQuestData;
class UQuestObjectiveData;
class UQuestStageData;
class UWholeQuest;

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
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bIsOptional;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bIsAlwaysActive;
	
	bool bIsCompleted = false;

	uint8 TimesCompleted = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UQuestObjectiveData> QuestData;

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

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UQuestStageData> QuestData;

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

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UWholeQuest> QuestData;

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
	
	UFUNCTION(BlueprintCallable)
	static void StartQuestAtIndex(uint8 QuestToStart, uint8 QuestStageToStart, UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FText GetParentQuestName(UQuestObjectiveData* Quest);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FText GetQuestDisplayName(UQuestObjectiveData* QuestData);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static uint8 GetActiveStageIndex(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static uint8 GetActiveQuestIndex(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FText GetQuestName(UWholeQuest* Quest);

};
