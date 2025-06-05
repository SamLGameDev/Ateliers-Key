// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BP_Player.generated.h"

class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;
class UInputAction;
class UActorList;

UCLASS()
class GAM390GAME_API ABP_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABP_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input");
	const UInputMappingContext* GameplayMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input");
	const UInputMappingContext* HackingMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	const UInputAction* StartHackingAction;

	void StartHacking();

	void StopHacking();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hacking")
	UActorList* HackableObjects;

	void EnableHackableObjectsHighlight();

	void DisableHackableObjectsHighlight();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SwitchToGameplayMap();

	void SwitchToHackingMap();

	void SwitchMap(const UInputMappingContext* Map, UEnhancedInputLocalPlayerSubsystem* Input);

};
