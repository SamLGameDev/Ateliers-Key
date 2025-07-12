// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Player.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "ActorList.h"
#include "HackableActor.h"
#include "BP_GeneralFunctions.h"
#include "GUI_HackingMenu.h"
#include "Hacks/HackEffect.h"
#include "HackEffectStore.h"
#include "GUI_HackSelector.h"
#include "TimeManager.h"
#include "TimeDialationToken.h"
#include "HackableEnemy.h"
#include "Hackable.h"

// Sets default values
ABP_Player::ABP_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABP_Player::BeginPlay()
{
	Super::BeginPlay();
	SwitchToGameplayMap();
	HackingMenu = CreateWidget<UGUI_HackingMenu>(GetWorld(), BPHackingMenu, "HackingMenu");
	HackSelector = CreateWidget<UGUI_HackSelector>(GetWorld(), BPHackSelector, "HackSelector");
	SetUpInputActions();
}

void ABP_Player::SetUpInputActions()
{
	SetUpHackingActions();
	SetUpHackSelectionActions();
}

void ABP_Player::SetUpHackSelectionActions()
{
	InputComp->BindAction(NextSlot, ETriggerEvent::Started, HackSelector, &UGUI_HackSelector::FocusNextSlot);
	InputComp->BindAction(NextSlot, ETriggerEvent::Triggered, HackSelector, &UGUI_HackSelector::FocusNextSlot);

	InputComp->BindAction(PreviousSlot, ETriggerEvent::Started, HackSelector, &UGUI_HackSelector::FocusPreviousSlot);
	InputComp->BindAction(PreviousSlot, ETriggerEvent::Triggered, HackSelector, &UGUI_HackSelector::FocusPreviousSlot);

	InputComp->BindAction(NextAvailableHack, ETriggerEvent::Started, HackSelector, &UGUI_HackSelector::FocusNextAvailableHack);
	InputComp->BindAction(NextAvailableHack, ETriggerEvent::Triggered, HackSelector, &UGUI_HackSelector::FocusNextAvailableHack);

	InputComp->BindAction(PreviousAvailableHack, ETriggerEvent::Started, HackSelector, &UGUI_HackSelector::FocusPreviousAvailableHack);
	InputComp->BindAction(PreviousAvailableHack, ETriggerEvent::Triggered, HackSelector, &UGUI_HackSelector::FocusPreviousAvailableHack);

	InputComp->BindAction(AddToSlot, ETriggerEvent::Started, HackSelector, &UGUI_HackSelector::LoadSelectedToSlot);
	InputComp->BindAction(ExitSelection, ETriggerEvent::Started, this, &ABP_Player::StopHackSelecton);
}

void ABP_Player::SetUpHackingActions()
{
	InputComp->BindAction(NextHack, ETriggerEvent::Started, HackingMenu, &UGUI_HackingMenu::FocusNextHackButton);
	InputComp->BindAction(NextHack, ETriggerEvent::Triggered, HackingMenu, &UGUI_HackingMenu::FocusNextHackButton);

	InputComp->BindAction(PrevHack, ETriggerEvent::Started, HackingMenu, &UGUI_HackingMenu::FocusPreviousHackButton);
	InputComp->BindAction(PrevHack, ETriggerEvent::Triggered, HackingMenu, &UGUI_HackingMenu::FocusPreviousHackButton);

	InputComp->BindAction(TriggerHack, ETriggerEvent::Started, HackingMenu, &UGUI_HackingMenu::TriggerHack);
}

void ABP_Player::StartHacking()
{
	if (!HackingMenu)
	{
		return;
	}
	HackingMenu->AddToViewport();
	SwitchToHackingMap();
	HackingDialation = UTimeManager::SetTimeDialation(this, 0.01);
	EnableHackableObjectsHighlight();
	HackingTraceHandle = OnTick.AddUFunction(this, NAMEOF(DisplayViewedHackableObject));
	HackingMenu->DisableHackButtons();
}

void ABP_Player::StopHacking()
{
	HackingMenu->RemoveFromParent();
	SwitchToGameplayMap();

	HackingDialation->StopDialation();

	DisableHackableObjectsHighlight();
	OnTick.Remove(HackingTraceHandle);
}

void ABP_Player::StopHackSelecton()
{
	HackSelector->Exit();
	SwitchToGameplayMap();
}

void ABP_Player::EnableHackableObjectsHighlight()
{
	for (AActor* Object : HackableObjects->GetRegisteredObjects())
	{
		AHackable* HObject = Cast<AHackable>(Object);
		HObject->EnableHighlight();
	}

}

void ABP_Player::DisableHackableObjectsHighlight()
{
	for (AActor* Object : HackableObjects->GetRegisteredObjects())
	{
		AHackable* HObject = Cast<AHackable>(Object);
		HObject->DisableHighlight();
	}

}

void ABP_Player::DisplayViewedHackableObject()
{
	FHitResult Result;

	APlayerCameraManager* CManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager.Get();

	FVector Start = CManager->GetCameraLocation();

	FVector Forward = CManager->GetActorForwardVector() * 2500;

	FCollisionObjectQueryParams Oparams;
	Oparams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel1);

	FCollisionQueryParams params;

	bool bhit = GetWorld()->LineTraceSingleByObjectType(Result, Start, Start + Forward, Oparams, params);
	if (bhit)
	{
		Print("Hello", nullptr);
		AHackable* Hackable = Cast<AHackable>(Result.GetActor());

		const TArray<UHackEffect*>& hacks = LoadedHacks->GetRegisteredObjects();

		HackingMenu->UpdateButtonDisplay(hacks);
		HackingMenu->SetFocusedObject(Hackable);
	}
	else
	{
		HackingMenu->DisableHackButtons();
	}
}

void ABP_Player::BeginDestroy()
{
	Super::BeginDestroy();
#if WITH_EDITOR
	if (AvailableHacks && LoadedHacks)
	{
		AvailableHacks->Clear();
		LoadedHacks->Clear();
	}

#endif
}

// Called every frame
void ABP_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
	OnTick.Broadcast();
	

}

// Called to bind functionality to input
void ABP_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if(InputComp)
	{
		InputComp->BindAction(StartHackingAction, ETriggerEvent::Started, this, &ABP_Player::StartHacking);
		InputComp->BindAction(StartHackingAction, ETriggerEvent::Completed, this, &ABP_Player::StopHacking);
	}
}

void ABP_Player::SwitchToGameplayMap()
{
	const APlayerController* playerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* input =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

	input->RemoveMappingContext(HackingMap);
	input->RemoveMappingContext(HackSelctionMap);

	SwitchMap(GameplayMap, input);
}

void ABP_Player::SwitchToHackingMap()
{
	const APlayerController* playerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* input =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

	input->RemoveMappingContext(GameplayMap);

	SwitchMap(HackingMap, input);
}

void ABP_Player::SwitchToHackingSelection()
{
	const APlayerController* playerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* input =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

	input->RemoveMappingContext(GameplayMap);
	input->RemoveMappingContext(HackingMap);

	SwitchMap(HackSelctionMap, input);
}

void ABP_Player::StartHackSelection()
{
	SwitchToHackingSelection();
	HackSelector->AddToViewport();
}

void ABP_Player::SwitchMap(const UInputMappingContext* Map, UEnhancedInputLocalPlayerSubsystem* Input)
{
	Input->AddMappingContext(Map, 0);
}

