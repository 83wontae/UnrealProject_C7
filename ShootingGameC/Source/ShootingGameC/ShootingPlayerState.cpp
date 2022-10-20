// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

void AShootingPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShootingPlayerState, Hp);
}

void AShootingPlayerState::UpdateHp()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
		FString::Printf(TEXT("UpdateHp Hp=%d"), Hp));
}

void AShootingPlayerState::AddDamage(int Damage)
{
	Hp -= Damage;
	
	if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->HasAuthority())
	{
		UpdateHp();
	}
}
