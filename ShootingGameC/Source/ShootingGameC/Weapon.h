// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WeaponInterface.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

USTRUCT(BlueprintType)
struct FStWeapon : public FTableRowBase
{
	GENERATED_BODY()

public:
	FStWeapon()
	: AnimMontage_Shoot(nullptr)
	, AnimMontage_Reload(nullptr)
	, FireEffect(nullptr)
	, StaticMesh(nullptr)
	{}

	//~ 다음 멤버 변수는 블루프린트 그래프를 통해 액세스할 수 있습니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* AnimMontage_Shoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* AnimMontage_Reload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* FireEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* StaticMesh;
};

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
	FName WeaponName;

	UDataTable* WeaponTable;

	FStWeapon* st_weapon;

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
