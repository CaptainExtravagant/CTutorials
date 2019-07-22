// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_FPS_O.generated.h"

UCLASS()
class CTUTORIALS_API AGM_FPS_O : public AGameModeBase
{
	GENERATED_BODY()

	virtual void StartPlay() override;
};
