// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter_O.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AFPSCharacter_O::AFPSCharacter_O()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPSCameraComponent->SetupAttachment(GetCapsuleComponent());

	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	FPSCameraComponent->bUsePawnControlRotation = true;

	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	
	FPSMesh->SetOnlyOwnerSee(true);
	
	FPSMesh->SetupAttachment(FPSCameraComponent);

	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	GetMesh()->SetOwnerNoSee(true);
}

// Called when the game starts or when spawned
void AFPSCharacter_O::BeginPlay()
{
	Super::BeginPlay();
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Using Custom FPS Character"));
	}
}

// Called every frame
void AFPSCharacter_O::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter_O::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveX", this, &AFPSCharacter_O::MoveForward);
	PlayerInputComponent->BindAxis("MoveY", this, &AFPSCharacter_O::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter_O::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter_O::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter_O::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter_O::StopJump);
}

void AFPSCharacter_O::MoveForward(float value)
{
	FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(direction, value);
}

void AFPSCharacter_O::MoveRight(float value)
{
	FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(direction, value);
}

void AFPSCharacter_O::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter_O::StopJump()
{
	bPressedJump = false;
}