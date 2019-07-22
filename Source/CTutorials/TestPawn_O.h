// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TestPawn_O.generated.h"

UCLASS()
class CTUTORIALS_API ATestPawn_O : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATestPawn_O();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		USceneComponent* visibleComponent;

	void Move_XAxis(float axisValue);
	void Move_YAxis(float axisValue);
	void StartGrowing();
	void StopGrowing();

	FVector currentVelocity;
	bool bGrowing;
};
