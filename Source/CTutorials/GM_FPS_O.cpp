// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_FPS_O.h"

void AGM_FPS_O::StartPlay()
{
	Super::StartPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is the FPS Gamemode"));
	}
}