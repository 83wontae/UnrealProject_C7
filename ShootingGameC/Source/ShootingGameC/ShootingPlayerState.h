// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ShootingPlayerState.generated.h"

DECLARE_DELEGATE(FDele_UpdateHp);
DECLARE_DELEGATE_OneParam(FDele_UpdateHp_OneParam, int);

/**
 * 
 */
UCLASS()
class SHOOTINGGAMEC_API AShootingPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AShootingPlayerState();

protected:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth)
	float CurrentHealth;

	UFUNCTION()
	void OnRep_CurrentHealth();

public:
	void OnUpdateHp();

	/** Getter for Current Health.*/
	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }


	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddDamage(float Damage);

	FDele_UpdateHp Fuc_Dele_UpdateHp;
	FDele_UpdateHp_OneParam Fuc_Dele_UpdateHp_OneParam;
};
