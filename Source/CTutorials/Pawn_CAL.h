// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pawn_CAL.generated.h"

UCLASS()
class CTUTORIALS_API APawn_CAL : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawn_CAL();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Inputs
	void MoveX(float axisValue);
	void MoveY(float axisValue);
	void StartGrow();
	void StopGrow();

	// Input Variables
	FVector currentVelocity;
	bool isGrowing;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* staticMesh;
};
