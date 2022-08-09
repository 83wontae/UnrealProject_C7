// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BountyDash.h"
#include "BountyDashObject.h"
#include "Obstacle.generated.h"

class UDestructibleComponent;

UCLASS()
class BOUNTYDASH_API AObstacle : public ABountyDashObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();

	UDestructibleComponent* GetDestructable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDestructibleComponent* Mesh;
};
