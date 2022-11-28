// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObjectInterface.h"
#include "GameFramework/PlayerState.h"
#include "ShootingPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FDele_Multi_UpdateHp);
DECLARE_MULTICAST_DELEGATE_OneParam(FDele_Multi_UpdateHp_OneParam, float);

/**
 *
 */
UCLASS()
class SHOOTINGGAMEC_API AShootingPlayerState : public APlayerState, public IItemObjectInterface
{
	GENERATED_BODY()

public:
	AShootingPlayerState();

protected:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth)
	float CurrentHealth;

public:
	UFUNCTION()
	void OnRep_CurrentHealth();

	/** Getter for Current Health.*/
	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddDamage(float Damage);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddHealth(float Heal);

	virtual void AddHealth_Implementation(float Heal) override;

	FDele_Multi_UpdateHp Fuc_Dele_UpdateHp;
	FDele_Multi_UpdateHp_OneParam Fuc_Dele_UpdateHp_OneParam;
};
