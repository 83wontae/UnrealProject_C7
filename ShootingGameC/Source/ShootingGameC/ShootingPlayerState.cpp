// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

AShootingPlayerState::AShootingPlayerState()
{
	CurrentHealth = 100.0f;
}

void AShootingPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShootingPlayerState, CurrentHealth);
}

void AShootingPlayerState::OnRep_CurrentHealth()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
		FString::Printf(TEXT("UpdateHp CurrentHealth=%f"), GetCurrentHealth()));

	Fuc_Dele_UpdateHp.ExecuteIfBound();
	Fuc_Dele_UpdateHp_OneParam.ExecuteIfBound(GetCurrentHealth());
}

void AShootingPlayerState::AddDamage(float Damage)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			FString::Printf(TEXT("AddDamage CurrentHealth=%f , Damage=%f"), GetCurrentHealth(), Damage));

		CurrentHealth = CurrentHealth - Damage;

		OnRep_CurrentHealth();
	}
}
