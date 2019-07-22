// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPawn_O.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ATestPawn_O::ATestPawn_O()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	UCameraComponent* camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	visibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleComponent"));	

	camera->SetupAttachment(RootComponent);
	camera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	camera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	visibleComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATestPawn_O::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestPawn_O::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float currentScale = visibleComponent->GetComponentScale().X;
	if (bGrowing)
	{
		currentScale += DeltaTime;
	}
	else
	{
		currentScale -= (DeltaTime * 0.5f);
	}

	currentScale = FMath::Clamp(currentScale, 1.0f, 2.0f);
	visibleComponent->SetWorldScale3D(FVector(currentScale));

	if (!currentVelocity.IsZero())
	{
		FVector newLocation = GetActorLocation() + (currentVelocity * DeltaTime);
		SetActorLocation(newLocation);
	}

}

// Called to bind functionality to input
void ATestPawn_O::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Grow", IE_Pressed, this, &ATestPawn_O::StartGrowing);
	PlayerInputComponent->BindAction("Grow", IE_Released, this, &ATestPawn_O::StopGrowing);

	PlayerInputComponent->BindAxis("MoveX", this, &ATestPawn_O::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &ATestPawn_O::Move_YAxis);

}

void ATestPawn_O::Move_XAxis(float axisValue)
{
	currentVelocity.X = FMath::Clamp(axisValue, -1.0f, 1.0f) * 100.0f;
}

void ATestPawn_O::Move_YAxis(float axisValue)
{
	currentVelocity.Y = FMath::Clamp(axisValue, -1.0f, 1.0f) * 100.0f;
}

void ATestPawn_O::StartGrowing()
{
	bGrowing = true;
}

void ATestPawn_O::StopGrowing()
{
	bGrowing = false;
}
