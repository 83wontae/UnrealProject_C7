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
#include "ShootingGameHUD.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	bool bIsImplemented = GetClass()->ImplementsInterface(UWeaponInterface::StaticClass());

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	CurrentAmmo = 30;

	static ConstructorHelpers::FObjectFinder<UDataTable> datatable(TEXT("DataTable'/Game/ShootingGame/GameMode/NewDataTable.NewDataTable'"));

	if (datatable.Succeeded())
	{
		WeaponTable = datatable.Object;
	}
}

void AWeapon::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeapon, OwnChar);
	DOREPLIFETIME(AWeapon, WeaponName);
	DOREPLIFETIME(AWeapon, CurrentAmmo);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (WeaponTable)
	{
		auto List = WeaponTable->GetRowNames();
		//WeaponName = List[FMath::RandRange(0, List.Num() - 1)];
		WeaponName = List[0];
		st_weapon = WeaponTable->FindRow<FStWeapon>(WeaponName, FString(""));
		if (st_weapon)
		{
			mesh->SetStaticMesh(st_weapon->StaticMesh);
			mesh->SetCollisionProfileName(TEXT("Weapon"));
			mesh->SetSimulatePhysics(true);
		}
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::ServerPullTrigger_Implementation()
{
	if (IsCanShoot())
	{
		UseAmmo();
	}

	MulticastPullTrigger();
}

void AWeapon::MulticastPullTrigger_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("MulticastPullTrigger_Implementation"));

	check(OwnChar);
	check(st_weapon);

	OwnChar->PlayAnimMontage(st_weapon->AnimMontage_Shoot);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), st_weapon->FireEffect
		, mesh->GetSocketLocation("muzzle"), mesh->GetSocketRotation("muzzle"), FVector(0.2f, 0.2f, 0.2f));
}

void AWeapon::ServerReload_Implementation()
{
	MulticastReload();
}

void AWeapon::MulticastReload_Implementation()
{
	check(OwnChar);
	check(st_weapon->AnimMontage_Reload);

	OwnChar->PlayAnimMontage(st_weapon->AnimMontage_Reload);
}

void AWeapon::ServerNotifyShoot_Implementation(const FVector vStart, const FVector vEnd)
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

}

void AWeapon::PressKey_Shoot_Implementation()
{
	ServerPullTrigger();
}

void AWeapon::PressKey_R_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("PressKey_R_Implementation"));
	ServerReload();
}

void AWeapon::NotifyShoot_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("PressKey_F_Implementation"));

	APlayerController* caster = Cast<APlayerController>(OwnChar->Controller);
	if (caster)
	{
		FVector vForward = caster->PlayerCameraManager->GetActorForwardVector();
		FVector vStart = caster->PlayerCameraManager->GetCameraLocation() + (vForward * 300);
		FVector vEnd = vStart + (vForward * 5000);
		ServerNotifyShoot(vStart, vEnd);
	}
}

void AWeapon::NotifyReload_Implementation()
{
	DoReload();
}

void AWeapon::OnCharacterEquip_Implementation(ACharacter* targetChar)
{
	OwnChar = targetChar;
	mesh->SetSimulatePhysics(false);
	mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mesh->AttachToComponent(targetChar->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "weapon");
	OnUpdateHUD();
}

void AWeapon::OnRep_CurrentAmmo()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,	FString::Printf(TEXT("OnRep_CurrentAmmo CurrentAmmo=%f"), GetCurrentAmmo()));

	OnUpdateHUD();
}

void AWeapon::UseAmmo()
{
	CurrentAmmo = CurrentAmmo - 1;

	if (GetLocalRole() == ROLE_Authority)
	{
		OnRep_CurrentAmmo();
	}
}

void AWeapon::DoReload()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		CurrentAmmo = 30;

		OnRep_CurrentAmmo();
	}
}

void AWeapon::OnUpdateHUD()
{
	APlayerController* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (OwnChar->GetController() == pc)
	{
		AShootingGameHUD* hud = Cast<AShootingGameHUD>(pc->GetHUD());
		hud->OnUpdateAmmo(GetCurrentAmmo());
	}
}

