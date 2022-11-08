// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponInterface.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class SHOOTINGGAMEC_API AWeapon : public AActor, public IWeaponInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(Server, Reliable)
	void ServerPullTrigger();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastPullTrigger();

	UFUNCTION(Server, Reliable)
	void ServerReload();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastReload();

	UFUNCTION(Server, Reliable)
	void ServerNotifyShoot(const FVector vStart, const FVector vEnd);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* mesh;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Default", Meta = (ExposeOnSpawn = "true"))
	ACharacter* OwnChar;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Default", Meta = (ExposeOnSpawn = "true"))
	UAnimMontage* AnimMontage_Shoot;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Default", Meta = (ExposeOnSpawn = "true"))
	UAnimMontage* AnimMontage_Reload;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Default", Meta = (ExposeOnSpawn = "true"))
	UParticleSystem* FireEffect;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentAmmo)
	int CurrentAmmo;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PressKey_Shoot();
	
	virtual void PressKey_Shoot_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ReleasedKey_Shoot();

	virtual void ReleasedKey_Shoot_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PressKey_R();

	virtual void PressKey_R_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void NotifyShoot();

	virtual void NotifyShoot_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void NotifyReload();

	virtual void NotifyReload_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnCharacterEquip(ACharacter* targetChar);

	virtual void OnCharacterEquip_Implementation(ACharacter* targetChar) override;

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsCanShoot() const { return (CurrentAmmo > 0) ? true : false; }

	UFUNCTION()
	void OnRep_CurrentAmmo();

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetCurrentAmmo() const { return CurrentAmmo; }

	UFUNCTION(BlueprintCallable)
	void UseAmmo();

	UFUNCTION(BlueprintCallable)
	void DoReload();

	UFUNCTION(BlueprintCallable)
	void OnUpdateHUD();
};
