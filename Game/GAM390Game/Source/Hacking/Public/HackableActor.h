// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hackable.h"
#include "HackableActor.generated.h"

class UDecalComponent;
class UActorList;
class UHackEffect;
class UWidgetComponent;

UCLASS()
class HACKING_API AHackableActor : public AHackable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHackableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
