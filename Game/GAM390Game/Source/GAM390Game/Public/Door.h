// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class USplineComponent;
class UCameraShakeBase;


UCLASS()
class GAM390GAME_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();
		UFUNCTION(BlueprintCallable)
    	float const Fall();
		
		UFUNCTION(BlueprintCallable)
		const void Close();
	
    protected:
    
    	UPROPERTY(EditAnywhere)
    	UStaticMeshComponent* m_Mesh;
    	
    	UPROPERTY(EditAnywhere)
    	USplineComponent* Path;
    
    	UPROPERTY(EditAnywhere)
    	USceneComponent* m_RootComp;
    
    	UPROPERTY(EditAnywhere)
    	float m_Speed;
		
		UPROPERTY(EditAnywhere)
		USceneComponent* MeshRoot;
	
    	UFUNCTION()
    	void MoveMeshTowardsEnd(float alpha);

};
