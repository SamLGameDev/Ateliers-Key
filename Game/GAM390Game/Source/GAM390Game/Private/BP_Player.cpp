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

}


void ABP_Player::StartHacking()
{
	HackingMenu->AddToViewport();
	SwitchToHackingMap();
	GetWorld()->GetWorldSettings()->SetTimeDilation(0.01f);
	EnableHackableObjectsHighlight();
	HackingTraceHandle = OnTick.AddUFunction(this, NAMEOF(DisplayViewedHackableObject));
}

void ABP_Player::StopHacking()
{
	HackingMenu->RemoveFromParent();
	SwitchToGameplayMap();
	GetWorld()->GetWorldSettings()->SetTimeDilation(1);
	DisableHackableObjectsHighlight();
	OnTick.Remove(HackingTraceHandle);
}

void ABP_Player::EnableHackableObjectsHighlight()
{
	for (AActor* Object : HackableObjects->GetRegisteredObjects())
	{
		AHackableActor* HObject = Cast<AHackableActor>(Object);
		HObject->EnableHighlight();
	}
}

void ABP_Player::DisableHackableObjectsHighlight()
{
	for (AActor* Object : HackableObjects->GetRegisteredObjects())
	{
		AHackableActor* HObject = Cast<AHackableActor>(Object);
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
		AHackableActor* Hackable = Cast<AHackableActor>(Result.GetActor());
		for (UHackEffect* Hack : Hackable->GetHacks())
		{
			Hack->ExecuteHack(Hackable);
		}
	}
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
	UEnhancedInputComponent* enhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if(enhancedInput)
	{
		enhancedInput->BindAction(StartHackingAction, ETriggerEvent::Started, this, &ABP_Player::StartHacking);
		enhancedInput->BindAction(StartHackingAction, ETriggerEvent::Completed, this, &ABP_Player::StopHacking);
	}
}

void ABP_Player::SwitchToGameplayMap()
{
	const APlayerController* playerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* input =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

	input->RemoveMappingContext(HackingMap);

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

void ABP_Player::SwitchMap(const UInputMappingContext* Map, UEnhancedInputLocalPlayerSubsystem* Input)
{
	Input->AddMappingContext(Map, 0);
}

