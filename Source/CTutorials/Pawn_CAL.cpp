// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn_CAL.h"
#include "Camera/CameraComponent.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"

// Sets default values
APawn_CAL::APawn_CAL()
{
	// AutoPosses with Player ZERO
	AutoPossessPlayer = EAutoReceiveInput::Player0;

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Dummy Root
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Create Cam
	UCameraComponent* camComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("camComponent"));
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));
	// Attach Cam and Static Mesh to our Dummy Root. Offest and Rotated Cam
	camComponent->SetupAttachment(RootComponent);
	camComponent->SetRelativeLocation(FVector(-250.f, 0.0f, 250.0f));
	camComponent->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	staticMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APawn_CAL::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawn_CAL::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Growing and Shrinking
	{
		float currentScale = staticMesh->GetComponentScale().X;
		if (isGrowing)
		{
			// Double Size (1 Second)
			currentScale += DeltaTime;
		}
		else
		{
			// Shrink 
			currentScale -= DeltaTime;
		}

		// Never drop below starting size
		currentScale = FMath::Clamp(currentScale, 1.0f, 2.0f);
		staticMesh->SetWorldScale3D(FVector(currentScale));
	}

	{
		if (!currentVelocity.IsZero())
		{
			FVector newLocation = GetActorLocation() + (currentVelocity * DeltaTime);
			SetActorLocation(newLocation);
		}
	}
}

// Called to bind functionality to input
void APawn_CAL::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Grow
	PlayerInputComponent->BindAction("Grow", IE_Pressed, this, &APawn_CAL::StartGrow);
	PlayerInputComponent->BindAction("Grow", IE_Released, this, &APawn_CAL::StopGrow);
	// Movement
	PlayerInputComponent->BindAxis("MoveX", this, &APawn_CAL::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &APawn_CAL::MoveY);
}

void APawn_CAL::MoveX(float axisValue)
{
	// Move (500ups) Forward or Back
	currentVelocity.X = FMath::Clamp(axisValue, -1.0f, 1.0f) * 500.0f;
}

void APawn_CAL::MoveY(float axisValue)
{
	// Move (500ups) Left or Right
	currentVelocity.Y = FMath::Clamp(axisValue, -1.0f, 1.0f) * 500.0f;
}

void APawn_CAL::StartGrow()
{
	isGrowing = true;
}

void APawn_CAL::StopGrow()
{
	isGrowing = false;
}