// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "WeaponInterface.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "DrawDebugHelpers.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	bool bIsImplemented = GetClass()->ImplementsInterface(UWeaponInterface::StaticClass());

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

void AWeapon::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeapon, OwnChar);
	DOREPLIFETIME(AWeapon, AnimMontage_Shoot);
	DOREPLIFETIME(AWeapon, FireEffect);
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

void AWeapon::ServerPullTrigger_Implementation(const FVector vStart, const FVector vEnd)
{
	FHitResult result;
	bool isHit = GetWorld()->LineTraceSingleByObjectType(result, vStart, vEnd, ECollisionChannel::ECC_Pawn);

	DrawDebugLine(GetWorld(), vStart, vEnd, FColor::Yellow, false, 5.0f);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ServerPullTrigger_Implementation"));

	if (isHit)
	{
		FString actorName;
		result.GetActor()->GetName(actorName);

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
		//	FString::Printf(TEXT("ServerPullTrigger HitActor-%s"), *actorName));

		if (result.GetActor())
		{
			UGameplayStatics::ApplyDamage(result.GetActor(), 10, 
				result.GetActor()->GetInstigatorController(), this, UDamageType::StaticClass());
		}
	}

	MulticastPullTrigger();
}

void AWeapon::MulticastPullTrigger_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("MulticastPullTrigger_Implementation"));

	check(OwnChar);
	check(AnimMontage_Shoot);
	check(FireEffect);

	OwnChar->PlayAnimMontage(AnimMontage_Shoot);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireEffect
		, mesh->GetSocketLocation("muzzle"), mesh->GetSocketRotation("muzzle"), FVector(0.2f, 0.2f, 0.2f));
}

void AWeapon::PressKey_F_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("PressKey_F_Implementation"));

	APlayerController* caster = Cast<APlayerController>(OwnChar->Controller);
	if (caster)
	{
		FVector vForward = caster->PlayerCameraManager->GetActorForwardVector();
		FVector vStart = caster->PlayerCameraManager->GetCameraLocation() + (vForward * 300);
		FVector vEnd = vStart + (vForward * 5000);
		ServerPullTrigger(vStart, vEnd);
	}
}

