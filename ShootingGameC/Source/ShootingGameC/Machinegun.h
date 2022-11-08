// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Machinegun.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAMEC_API AMachinegun : public AWeapon
{
	GENERATED_BODY()
	
public:
	virtual void PressKey_Shoot_Implementation() override;

	virtual void ReleasedKey_Shoot_Implementation() override;

	void LoopShooting();

protected:
	FTimerHandle th_LoopShooting;
};
