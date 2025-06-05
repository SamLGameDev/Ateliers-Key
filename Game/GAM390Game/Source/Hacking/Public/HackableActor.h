// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HackableActor.generated.h"

class UDecalComponent;
class UActorList;

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


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
