// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Countdown_O.generated.h"

class UTextRenderComponent;

UCLASS()
class CTUTORIALS_API ACountdown_O : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ACountdown_O();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//How long, in seconds, the countdown will run
	UPROPERTY(EditAnywhere)
		int32 countdownTime;

	UTextRenderComponent* countdownText;

	void UpdateTimerDisplay();

	void AdvanceTimer();

	UFUNCTION(BlueprintNativeEvent)
		void CountdownFinished();
	virtual void CountdownFinished_Implementation();

	FTimerHandle countdownTimer;
};
