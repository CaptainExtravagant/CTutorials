// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector_CAL.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirector_CAL::ACameraDirector_CAL()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector_CAL::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector_CAL::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float timeBetweenCameraChanges = 2.0f;
	const float smoothBlendTime = 0.75f;
	timeToNextCameraChange -= DeltaTime;

	if (timeToNextCameraChange <= 0.0f)
	{
		timeToNextCameraChange += timeBetweenCameraChanges;

		// Get Player Controller
		APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
		if (playerController)
		{
			// If the first camera is not the view target of the player controller and is also not null...
			if ((playerController->GetViewTarget() != cameraOne) && (cameraOne != nullptr))
			{
				// Cut to camera one
				playerController->SetViewTarget(cameraOne);
			}
			else if ((playerController->GetViewTarget() != cameraTwo) && (cameraTwo != nullptr))
			{
				// Blend to camera two
				playerController->SetViewTargetWithBlend(cameraTwo, smoothBlendTime);
			}
		}
	}

}

