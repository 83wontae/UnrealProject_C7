// Fill out your copyright notice in the Description page of Project Settings.


#include "HealObject.h"
#include "ItemObjectInterface.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerState.h"

void AHealObject::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority() == false)
		return;

	ACharacter* OverlapChar = Cast<ACharacter>(OtherActor);
	if (OverlapChar == nullptr)
		return;

	IItemObjectInterface* interface = Cast<IItemObjectInterface>(OverlapChar->GetPlayerState());
	if (interface == nullptr)
		return;

	if (interface)
	{
		interface->Execute_AddHealth(OverlapChar->GetPlayerState(), 10);
	}
}
