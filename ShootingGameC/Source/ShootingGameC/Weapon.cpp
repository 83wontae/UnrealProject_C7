// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "WeaponInterface.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bool bIsImplemented = GetClass()->ImplementsInterface(UWeaponInterface::StaticClass());

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::PressKey_F_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Press Key F"));
}

