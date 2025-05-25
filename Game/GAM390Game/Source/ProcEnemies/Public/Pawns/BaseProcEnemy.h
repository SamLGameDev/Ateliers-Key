// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseProcEnemy.generated.h"

class UPawnSensingComponent;
class ABaseBodyPart;
class ABaseLeftArmPart;
class ABaseTorsoPart;
class ABaseHeadPart;
class ABaseLegPart;
class ABaseRightArmPart;
class UBaseArchetype;

UCLASS(Abstract)
class PROCENEMIES_API ABaseProcEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseProcEnemy();

#pragma region GettersAndSetters



	UFUNCTION()
	virtual void SetHead(ABaseHeadPart* InHead)
	{
		Head = InHead;
	}

	UFUNCTION()
	virtual void SetTorso(ABaseTorsoPart* InTorso)
	{
		Torso = InTorso;
	}

	UFUNCTION()
	virtual void SetLegs(ABaseLegPart* InLegs)
	{
		Legs = InLegs;
	}

	UFUNCTION()
	virtual void SetLeftArm(ABaseLeftArmPart* InArm)
	{
		LeftArm = InArm;
	}

	UFUNCTION()
	virtual void SetRightArm(ABaseRightArmPart* InArm)
	{
		RightArm = InArm;
	}

	UFUNCTION(BlueprintCallable)
	virtual ABaseHeadPart* GetHead() const
	{
		return Head;
	}

	UFUNCTION(BlueprintCallable)
	virtual ABaseTorsoPart* GetTorso() const
	{
		return Torso;
	}

	UFUNCTION(BlueprintCallable)
	virtual ABaseLegPart* GetLegs() const
	{
		return Legs;
	}

	UFUNCTION(BlueprintCallable)
	virtual ABaseLeftArmPart* GetLeftArm() const
	{
		return LeftArm;
	}

	UFUNCTION(BlueprintCallable)
	virtual ABaseRightArmPart* GetRightArm() const
	{
		return RightArm;
	}

	UFUNCTION()
	virtual void SetHeadSocketName(FName InName)
	{
		HeadSocketName = InName;
	}

	UFUNCTION()
	virtual void SetTorsoSocketName(FName InName)
	{
		TorsoSocketName = InName;
	}

	UFUNCTION()
	virtual void SetLegsSocketName(FName InName)
	{
		LegsSocketName = InName;
	}

	UFUNCTION()
	virtual void SetLeftArmSocketName(FName InName)
	{
		LeftArmSocketName = InName;
	}

	UFUNCTION()
	virtual void SetRigthArmSocketName(FName InName)
	{
		RightArmSocketName = InName;
	}

	UFUNCTION(BlueprintCallable)
	virtual const FName GetHeadSocketName() const
	{
		return HeadSocketName;
	}

	UFUNCTION(BlueprintCallable)
	virtual const FName GetTorsoSocketName() const
	{
		return TorsoSocketName;
	}

	UFUNCTION(BlueprintCallable)
	virtual const FName GetLegsSocketName() const
	{
		return LegsSocketName;
	}

	UFUNCTION(BlueprintCallable)
	virtual const FName GetLeftArmSocketName() const
	{
		return LeftArmSocketName;
	}

	UFUNCTION(BlueprintCallable)
	virtual const FName GetRightArmSocketName() const
	{
		return RightArmSocketName;
	}
#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UPawnSensingComponent* Sensor;

	UPROPERTY(VisibleAnywhere)
	ABaseLeftArmPart* LeftArm;

	UPROPERTY(VisibleAnywhere)
	ABaseRightArmPart* RightArm;

	UPROPERTY(VisibleAnywhere)
	ABaseHeadPart* Head;

	UPROPERTY(VisibleAnywhere)
	ABaseLegPart* Legs;

	UPROPERTY(VisibleAnywhere)
	ABaseTorsoPart* Torso;

	UPROPERTY(EditAnywhere)
	FName HeadSocketName;

	UPROPERTY(EditAnywhere)
	FName TorsoSocketName;

	UPROPERTY(EditAnywhere)
	FName LegsSocketName;

	UPROPERTY(EditAnywhere)
	FName LeftArmSocketName;

	UPROPERTY(EditAnywhere)
	FName RightArmSocketName;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UBaseArchetype>> Archetypes;

	UPROPERTY(EditAnywhere)
	FVector2D ThreatRange;

	UPROPERTY()
	UBaseArchetype* Archetype;


	struct FCompleteBody
	{

	public:
		ABaseBodyPart* Head;
		ABaseBodyPart* Torso;
		ABaseBodyPart* Legs;
		ABaseBodyPart* LeftArm;
		ABaseBodyPart* RightArm;

		FCompleteBody(
			ABaseBodyPart* InHead,
			ABaseBodyPart* InTorso,
			ABaseBodyPart* InLegs,
			ABaseBodyPart* InLeftArm,
			ABaseBodyPart* InRightArm
		) : Head(InLeftArm), Torso(InTorso), Legs(InLegs), LeftArm(InLeftArm), RightArm(InRightArm) {};
	};

	virtual void GetAllPossibleCombinationsOfParts(TArray<FCompleteBody>& PossibleComs, int HeadIndex, int TorsoIndex, int LegsIndex, int LeftArmIndex, int RightArmIndex);



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
