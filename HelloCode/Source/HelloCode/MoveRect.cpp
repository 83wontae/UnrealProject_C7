// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveRect.h"

// Sets default values
AMoveRect::AMoveRect() :MoveType{ EMoveRect::Rect_Right }
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(Scene);

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Rock.SM_Rock'"));

	if (MeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
	}
}

// Called when the game starts or when spawned
void AMoveRect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMoveRect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch(MoveType)
	{
		case EMoveRect::Rect_Right:
			Mesh->AddRelativeLocation(FVector(10.0f, 0.0f, 0.0f));
			if (Mesh->GetRelativeLocation().X >= 500)
				MoveType = EMoveRect::Rect_Up;
			break;

		case EMoveRect::Rect_Up:
			Mesh->AddRelativeLocation(FVector(0.0f, 0.0f, 10.0f));
			if (Mesh->GetRelativeLocation().Z >= 500)
				MoveType = EMoveRect::Rect_Left;
			break;

		case EMoveRect::Rect_Left:
			Mesh->AddRelativeLocation(FVector(-10.0f, 0.0f, 0.0f));
			if (Mesh->GetRelativeLocation().X <= 0)
				MoveType = EMoveRect::Rect_Down;
			break;

		case EMoveRect::Rect_Down:
			Mesh->AddRelativeLocation(FVector(0.0f, 0.0f, -10.0f));
			if (Mesh->GetRelativeLocation().Z <= 0)
				MoveType = EMoveRect::Rect_Right;
			break;
		default:	break;
	}
}

