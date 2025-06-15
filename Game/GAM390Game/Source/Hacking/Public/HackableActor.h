// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HackableActor.generated.h"

class UDecalComponent;
class UActorList;
class UHackEffect;
class UWidgetComponent;

UCLASS()
class HACKING_API AHackableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHackableActor();

	UFUNCTION(BlueprintCallable)
	void EnableHighlight();

	UFUNCTION(BlueprintCallable)
	void DisableHighlight();

	UFUNCTION(BlueprintCallable)
	TArray<UHackEffect*>& GetHacks()
	{
		return AvailableHacks;
	}

	void SetLoadingBarProgress(const float Percent);

	void EnableLoadingBar();

	void DisableLoadingBar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UActorList* HackableObjects;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* HackableObejctOutline;

	UPROPERTY(EditAnywhere)
	TArray<UHackEffect*> AvailableHacks;

	UPROPERTY(EditAnyWhere)
	UWidgetComponent* LoadingBar;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
