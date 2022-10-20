// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ShootingPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAMEC_API AShootingPlayerState : public APlayerState
{
	GENERATED_BODY()
	

public:
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = UpdateHp)
	int Hp;

	UFUNCTION()
	void UpdateHp();

	void AddDamage(int Damage);
};
