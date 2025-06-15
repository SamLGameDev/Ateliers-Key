// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BP_Player.generated.h"

class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;
class UInputAction;
class UActorList;
class UGUI_HackingMenu;
class UEnhancedInputComponent;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	const UInputAction* NextHack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	const UInputAction* PrevHack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	const UInputAction* TriggerHack;

	void StartHacking();

	void StopHacking();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hacking")
	UActorList* HackableObjects;

	void EnableHackableObjectsHighlight();

	void DisableHackableObjectsHighlight();

	DECLARE_MULTICAST_DELEGATE(FOnTickSignature);
	FOnTickSignature OnTick;

	UFUNCTION()
	void DisplayViewedHackableObject();

	FDelegateHandle HackingTraceHandle;

	UPROPERTY()
	UGUI_HackingMenu* HackingMenu;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGUI_HackingMenu> BPHackingMenu;

	UEnhancedInputComponent* InputComp;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SwitchToGameplayMap();

	void SwitchToHackingMap();

	void SwitchMap(const UInputMappingContext* Map, UEnhancedInputLocalPlayerSubsystem* Input);

};
