// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BountyDashObject.h"
#include "BountyDashPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class BOUNTYDASH_API ABountyDashPowerUp : public ABountyDashObject
{
	GENERATED_BODY()
	
public:
	ABountyDashPowerUp();

	virtual void MyOnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

private:
	class UPowerUpObject* PowerUp;
};
