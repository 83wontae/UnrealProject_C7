// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "Components/SphereComponent.h"
#include "DestructibleComponent.h"
#include "BountyDashGameModeBase.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Mesh"));
	check(Mesh);
	Mesh->AttachToComponent(Collider, FAttachmentTransformRules::KeepRelativeTransform);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
}

UDestructibleComponent* AObstacle::GetDestructable()
{
	return Mesh;
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}