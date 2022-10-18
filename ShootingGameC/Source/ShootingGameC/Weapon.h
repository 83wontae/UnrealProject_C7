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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* mesh;

	UPROPERTY(BlueprintReadWrite, Category = "Default", Meta = (ExposeOnSpawn = "true"))
	ACharacter* OwnChar;

	UPROPERTY(BlueprintReadWrite, Category = "Default", Meta = (ExposeOnSpawn = "true"))
	UAnimMontage* AnimMontage_Shoot;

	UPROPERTY(BlueprintReadWrite, Category = "Default", Meta = (ExposeOnSpawn = "true"))
	UParticleSystem* FireEffect;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PressKey_F();
	
	virtual void PressKey_F_Implementation() override;
};
