// Fill out your copyright notice in the Description page of Project Settings.


#include "HelloSphere.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AHelloSphere::AHelloSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 구체 컬리전 SphereComponent 생성
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	// SphereComponent를 RootComponent로 만든다.
	RootComponent = SphereComponent;
	// SphereComponent의 반지름 설정
	SphereComponent->InitSphereRadius(220.0f);
	// SphereComponent의 컬리전 프리셋 지정
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));


	// StaticMeshCompoent로 SphereVisual 생성
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	// SphereVisual을 RootComponent에 붙인다.
	SphereVisual->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	// Shape_Sphere 에셋을 찾아서 SphereAsset에 넣는다.
	ConstructorHelpers::FObjectFinder<UStaticMesh> SphereAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

	// M_Metal_Burnished_Steel 에셋을 찾아서 SphereMaterial에 넣는다.
	ConstructorHelpers::FObjectFinder<UMaterial> SphereMaterial(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Burnished_Steel.M_Metal_Burnished_Steel'"));

	if (SphereAsset.Succeeded() && SphereMaterial.Succeeded())
	{
		// SphereVisual에 SphereAsset 에셋 적용
		SphereVisual->SetStaticMesh(SphereAsset.Object);
		// SphereVisual에 메터리얼 적용
		SphereVisual->SetMaterial(0, SphereMaterial.Object);
		// SphereVisual에 위치값 적용
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	}

	// ParticleSystemComponent로 FireParticles 생성
	UParticleSystemComponent* FireParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireParticles"));

	// FireParticles을 SphereVisual에 붙인다.
	FireParticles->AttachToComponent(SphereVisual, FAttachmentTransformRules::KeepRelativeTransform);
	// FireParticles을 시작할때 자동으로 활성화 시킨다.
	FireParticles->bAutoActivate = true;

	// P_Fire에셋을 찾아서 FireVisual에 넣는다.
	ConstructorHelpers::FObjectFinder<UParticleSystem> FireVisual(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));

	if (FireVisual.Succeeded())
	{
		// FireParticles에 FireVisual 에셋을 적용 시킨다.
		FireParticles->SetTemplate(FireVisual.Object);
	}

	// UTextRenderComponent형의 TextRenderComponent 생성
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	// TextRenderComponent를 SphereVisual에 붙인다.
	TextRenderComponent->AttachToComponent(SphereVisual, FAttachmentTransformRules::KeepRelativeTransform);
	// TextRenderComponent의 위치 설정
	TextRenderComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));
	// TextRenderComponent를 중앙 정렬 시킨다.
	TextRenderComponent->SetHorizontalAlignment(EHTA_Center);
	// TextRenderComponent의 크기 설정
	TextRenderComponent->SetYScale(2.0f);
	TextRenderComponent->SetXScale(2.0f);
	// TextRenderComponent의 Visibility 설정
	TextRenderComponent->SetVisibility(true);
	// TextRenderComponent에 텍스트 적용
	// (NSLOCTEXT 메크로를 통해서 AnyNs 네임스페이스에 Any키에 HelloWorld 텍스트 지정)
	TextRenderComponent->SetText(NSLOCTEXT("AnyNs", "Any", "HelloWorld"));


	OnActorBeginOverlap.AddDynamic(this, &AHelloSphere::MyOnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AHelloSphere::MyOnEndOverlap);
}

// Called when the game starts or when spawned
void AHelloSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHelloSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHelloSphere::MyOnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FString outputString;
	outputString = "Hello" + OtherActor->GetName() + "!";
	TextRenderComponent->SetText(FText::FromString(outputString));
}

void AHelloSphere::MyOnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	TextRenderComponent->SetText(NSLOCTEXT("AnyNs", "Any", "HelloWorld"));
}
