// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector_CAL.generated.h"

UCLASS()
class CTUTORIALS_API ACameraDirector_CAL : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraDirector_CAL();

	UPROPERTY(EditAnywhere)
		AActor* cameraOne;
	UPROPERTY(EditAnywhere)
		AActor* cameraTwo;

	float timeToNextCameraChange;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};