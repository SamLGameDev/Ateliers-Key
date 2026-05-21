// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BP_SceneManager.generated.h"

/**
 * 
 */
UCLASS()
class LEVELMANAGERS_API UBP_SceneManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	/// <summary>
	/// normal loading from the next level, use when loading from a menu
	/// </summary>
	/// <param name="Level"></param>
	/// <param name="WorldContextObject"></param>
	/// <param name="TimedLevel"></param>
	UFUNCTION(BlueprintCallable, Category = "SceneManager|Level Loading")
	static void LoadLevel(FName Level, UObject* WorldContextObject);

	static void ClearAllTimers(UObject* WorldContextObject);

	static void Quit(UObject* WorldContextObject, APlayerController* Controller = nullptr);

	UFUNCTION(BlueprintCallable, Category = "SceneManager|Level Loading")
	static void ReloadLevel(UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category = "SceneManager|Level Loading")
	static void ReloadLevelStream(UObject* WorldContextObject, UWorld* ReloadedLevel);

	/// <summary>
	/// this is a list if timers to be cleared when changing scenes to stop crahses related to timers on objects that have been deleted;
	/// </summary>
	/// <param name="object"></param>
	UFUNCTION(BlueprintCallable, Category = "SceneManager|Timers")
	static void AddToTimersList(UObject* object) {
		ObjectsWithTimers.Add(object);
	}
	
	UFUNCTION(BlueprintCallable, Category = "SceneManager|Level Loading")
	static void FlushLevelStreamingFull(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SceneManager|Level Loading")
	static FString GetLevelName(TSoftObjectPtr<UWorld> Level);
	
private:

	static TArray<UObject*> ObjectsWithTimers;

};
