// Fill out your copyright notice in the Description page of Project Settings.


#include "Machinegun.h"
#include "Kismet/GameplayStatics.h"

void AMachinegun::PressKey_Shoot_Implementation()
{
	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	timerManager.SetTimer(th_LoopShooting, this, &AMachinegun::LoopShooting, 0.1f, true);
}

void AMachinegun::ReleasedKey_Shoot_Implementation()
{
	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	timerManager.ClearTimer(th_LoopShooting);
}

void AMachinegun::LoopShooting()
{
	ServerPullTrigger();
}