// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Pawn.h"
#include "ActorList.h"
#include "Hackable.generated.h"

class UHackEffect;

/**
 * 
 */
UCLASS()
class HACKING_API AHackable : public APawn
{
	GENERATED_BODY()

public:
	AHackable();

	void EnableHighlight();

	void DisableHighlight();

	UFUNCTION()
	void SetLoadingBarProgress(const float Percent);

	void EnableLoadingBar();

	void DisableLoadingBar();

	UFUNCTION(BlueprintCallable)
	virtual void StartHack(UHackEffect* Hack);

	UFUNCTION()
	void ProgressHack(UHackEffect* Hack, float TimeRemaining);

	UFUNCTION()
	void EndHack(UHackEffect* Hack);

	/// <summary>
	/// need base mesh so we can change the mesh overlay regardless of if it is a skeletal mesh or static mesh
	/// </summary>
	UMeshComponent* BaseMesh;

	virtual void BeginDestroy() override;

protected:

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UActorList* HackableObjects;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* HackableObejctOutline;

	UPROPERTY(EditAnyWhere)
	UWidgetComponent* LoadingBar;


};
