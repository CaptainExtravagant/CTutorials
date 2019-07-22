// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector_O.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirector_O::ACameraDirector_O()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector_O::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector_O::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float timeBetweenCameraChanges = 2.0f;
	const float smoothBlendTime = 0.75f;
	timeToNextCameraChange -= DeltaTime;

	if (timeToNextCameraChange <= 0.0f)
	{
		timeToNextCameraChange += timeBetweenCameraChanges;

		APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);

		if (playerController)
		{
			if ((playerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
			{
				playerController->SetViewTarget(CameraOne);
			}
			else if ((playerController->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
			{
				playerController->SetViewTargetWithBlend(CameraTwo, smoothBlendTime);
			}
		}
	}

}

