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
#include "Engine/UserInterfaceSettings.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

#define APPLICATION_ID 1506692667524907119

// Sets default values
ABP_Player::ABP_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABP_Player::SwitchToCoreMap()
{
	APlayerController* playerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* input =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

	SwitchMap(CoreMap, input);

	SwitchMap(AbilityMap, input);

	SwitchToGameplayMap();

	input->RemoveMappingContext(MenuMap);
	
	VirtualCursor->RemoveFromParent();
	
	//SimulateUIMouseClick();
	playerController->bShowMouseCursor = false;

	playerController->SetInputMode(FInputModeGameOnly());
	playerController->SetInputMode(FInputModeGameOnly());

}

// Called when the game starts or when spawned
void ABP_Player::BeginPlay()
{
	Super::BeginPlay();
	VirtualCursor = CreateWidget(GetWorld(), VirtualCursorClass);
	SetUpInputActions();
	SwitchToCoreMap();
}

void ABP_Player::SetUpMenuControls()
{
	InputComp->BindAction(MoveCursorGamepad, ETriggerEvent::Triggered, this, &ABP_Player::MoveCursorForGamepad);
	InputComp->BindAction(SelectGamepad, ETriggerEvent::Triggered, this, &ABP_Player::SimulateUIMouseClick);
}

void ABP_Player::SetUpInputActions()
{
	SetUpMenuControls();
}

void ABP_Player::SetUpHackSelectionActions()
{
	InputComp->BindAction(NextSlot, ETriggerEvent::Started, HackSelector, &UGUI_HackSelector::FocusNextSlot);
	InputComp->BindAction(NextSlot, ETriggerEvent::Completed, HackSelector, &UGUI_HackSelector::EndChamberRotation);

	InputComp->BindAction(PreviousSlot, ETriggerEvent::Started, HackSelector, &UGUI_HackSelector::FocusPreviousSlot);
	InputComp->BindAction(PreviousSlot, ETriggerEvent::Completed, HackSelector, &UGUI_HackSelector::EndChamberRotation);

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
}

void ABP_Player::StopHacking()
{
	HackingMenu->RemoveFromParent();
	SwitchToGameplayMap();

	HackingDialation->StopDialation();

	DisableHackableObjectsHighlight();
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


bool ABP_Player::DetectHitEntity(FHitResult& MeleeHit) const
{
	const FVector Start = GetActorLocation();
	const FVector End = Start + Cast<APlayerController>(GetController())->PlayerCameraManager->GetCameraRotation().Vector() * MeleeOffset;


	//Rotate it around the Z axis, so its facing the players direction, but not affecting the bounds
	const FQuat Rot = FRotator(0, GetControlRotation().Yaw,0).Quaternion();

	FCollisionObjectQueryParams CollisionObjectParams;
	CollisionObjectParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FCollisionShape CollisionBox = FCollisionShape::MakeBox(MeleeBoxHalfBounds);

	FCollisionQueryParams CollisionQueryParams;
	
	const bool bHit = GetWorld()->SweepSingleByObjectType
	(
		MeleeHit,
		End,
		End,
		Rot,
		CollisionObjectParams,
		FCollisionShape::MakeBox(MeleeBoxHalfBounds),
		CollisionQueryParams
	);

	return bHit;
}

void ABP_Player::Melee(UHackEffect* Hack)
{
	if (FHitResult MeleeHit; DetectHitEntity(MeleeHit))
	{
		FHackInfo HackInfo;
		HackInfo.Instigator = this;
		HackInfo.HackedObject = MeleeHit.GetActor();

		Hack->ExecuteHack(HackInfo);
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

void ABP_Player::LockGameplayInputs(const float Duration)
{

	const APlayerController* playerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* input =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

	input->RemoveMappingContext(GameplayMap);

	if (Duration == -1)
	{
		return;
	}

	FTimerDelegate lockInputDel;
	lockInputDel.BindUFunction(this, NAMEOF(UnLockGameplayInputs));

	GetWorld()->GetTimerManager().SetTimer(LockInputHandle, lockInputDel, Duration, false);

}

void ABP_Player::UnLockGameplayInputs()
{
	GetWorld()->GetTimerManager().ClearTimer(LockInputHandle);

	SwitchToGameplayMap();
}

void ABP_Player::SwitchToMenuControls()
{
	APlayerController* playerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* input =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

	input->RemoveMappingContext(GameplayMap);
	input->RemoveMappingContext(AbilityMap);

	SwitchMap(MenuMap, input);

	playerController->bShowMouseCursor = true;
	
	VirtualCursor->AddToViewport(99999999);
	
	SimulateUIMouseClick();
	

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

void ABP_Player::MoveCursorForGamepad(const FInputActionValue& Value)
{
	float MouseX, MouseY;
	GetWorld()->GetFirstPlayerController()->GetMousePosition(MouseX, MouseY);
	const FVector2D adjustment = Value.Get<FVector2D>();
	GetWorld()->GetFirstPlayerController()->SetMouseLocation(adjustment.X + MouseX, adjustment.Y + MouseY);
	VirtualCursor->SetPositionInViewport({adjustment.X + MouseX, adjustment.Y + MouseY});
}

void ABP_Player::SimulateUIMouseClick()
{
	FSlateApplication& app = FSlateApplication::Get();

	float mouseX, mouseY;
	GetWorld()->GetFirstPlayerController()->GetMousePosition(mouseX, mouseY);
	
	FPointerEvent MouseEvent(
		0,
		app.CursorPointerIndex,
		app.GetCursorPos(),
		app.GetLastCursorPos(),
		app.GetPressedMouseButtons(),
		EKeys::LeftMouseButton,
		0,
		app.GetPlatformApplication()->GetModifierKeys()
	);
	TSharedPtr<FGenericWindow, ESPMode::ThreadSafe> NullWindow;
	app.ProcessMouseButtonDownEvent(NullWindow, MouseEvent);

	app.ProcessMouseButtonUpEvent(MouseEvent);
}

