// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

AShootingPlayerState::AShootingPlayerState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	CurrentHealth = 100.0f;
}

void AShootingPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShootingPlayerState, CurrentHealth);
}

void AShootingPlayerState::OnRep_CurrentHealth()
{
	OnUpdateHp();
}

void AShootingPlayerState::OnUpdateHp()
{
	if (GetLocalRole() != ROLE_Authority)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			FString::Printf(TEXT("UpdateHp CurrentHealth=%d"), GetCurrentHealth()));

		Fuc_Dele_UpdateHp.ExecuteIfBound();
		Fuc_Dele_UpdateHp_OneParam.ExecuteIfBound(GetCurrentHealth());
	}
}

void AShootingPlayerState::AddDamage(float Damage)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			FString::Printf(TEXT("AddDamage CurrentHealth=%d , Damage=%d"), GetCurrentHealth(), Damage));

		CurrentHealth = CurrentHealth - Damage;

		OnRep_CurrentHealth();
	}
}
