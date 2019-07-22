// Fill out your copyright notice in the Description page of Project Settings.


#include "Countdown_O.h"
#include "Components/TextRenderComponent.h"
#include "TimerManager.h"

// Sets default values
ACountdown_O::ACountdown_O()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	countdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
	countdownText->SetHorizontalAlignment(EHTA_Center);
	countdownText->SetWorldSize(150.0f);
	RootComponent = countdownText;

	countdownTime = 3;
}

// Called when the game starts or when spawned
void ACountdown_O::BeginPlay()
{
	Super::BeginPlay();
	
	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(countdownTimer, this, &ACountdown_O::AdvanceTimer, 1.0f, true);
}

// Called every frame
void ACountdown_O::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACountdown_O::UpdateTimerDisplay()
{
	countdownText->SetText(FString::FromInt(FMath::Max(countdownTime, 0)));
}

void ACountdown_O::AdvanceTimer()
{
	--countdownTime;
	UpdateTimerDisplay();
	if (countdownTime < 1)
	{
		GetWorldTimerManager().ClearTimer(countdownTimer);
		CountdownFinished();
	}
}

void ACountdown_O::CountdownFinished_Implementation()
{
	countdownText->SetText(TEXT("GO!"));
}
