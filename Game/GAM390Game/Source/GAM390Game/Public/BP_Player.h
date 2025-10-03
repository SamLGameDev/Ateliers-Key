// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Hacks/HackEffect.h"
#include "BP_Player.generated.h"

class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;
class UInputAction;
class UActorList;
class UGUI_HackingMenu;
class UEnhancedInputComponent;
class UHackEffectStore;
class UGUI_HackSelector;
class UTimeDialationToken;

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

	void SetUpInputActions();

	void SetUpHackSelectionActions();

	void SetUpHackingActions();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input");
	const UInputMappingContext* GameplayMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input");
	const UInputMappingContext* HackingMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input");
	const UInputMappingContext* HackSelctionMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Hacking")
	const UInputAction* StartHackingAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Hacking")
	const UInputAction* NextHack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Hacking")
	const UInputAction* PrevHack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Hacking")
	const UInputAction* TriggerHack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|HackSelection")
	const UInputAction* NextSlot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|HackSelection")
	const UInputAction* PreviousSlot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|HackSelection")
	const UInputAction* AddToSlot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|HackSelection")
	const UInputAction* NextAvailableHack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|HackSelection")
	const UInputAction* PreviousAvailableHack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|HackSelection")
	const UInputAction* ExitSelection;

	UPROPERTY();
	UTimeDialationToken* HackingDialation;


	void StartHacking();

	void StopHacking();

	void StopHackSelecton();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hacking")
	UActorList* HackableObjects;

	void EnableHackableObjectsHighlight();

	void DisableHackableObjectsHighlight();

	DECLARE_MULTICAST_DELEGATE(FOnTickSignature);
	FOnTickSignature OnTick;

	FDelegateHandle HackingTraceHandle;

	UPROPERTY()
	UGUI_HackingMenu* HackingMenu;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGUI_HackingMenu> BPHackingMenu;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGUI_HackSelector> BPHackSelector;

	UPROPERTY()
	UGUI_HackSelector* HackSelector;

	UEnhancedInputComponent* InputComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHackEffectStore* AvailableHacks;

	UPROPERTY(EditDefaultsOnly)
	UHackEffectStore* LoadedHacks;

	virtual void BeginDestroy() override;
	bool DetectHitEntity(FHitResult& MeleeHit) const;

	UFUNCTION(BlueprintCallable)
	void Melee(UHackEffect* Hack);

	UPROPERTY(EditDefaultsOnly)
	float MeleeOffset;

	UPROPERTY(EditDefaultsOnly)
	FVector MeleeBoxHalfBounds;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SwitchToGameplayMap();

	void SwitchToHackingMap();

	void SwitchToHackingSelection();

	UFUNCTION(BlueprintCallable)
	void StartHackSelection();

	void SwitchMap(const UInputMappingContext* Map, UEnhancedInputLocalPlayerSubsystem* Input);


	

};
