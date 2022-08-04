// Fill out your copyright notice in the Description page of Project Settings.


#include "BountyDashCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/TargetPoint.h"
#include "EngineUtils.h"

// Sets default values
ABountyDashCharacter::ABountyDashCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �ݸ��� ĸ�� ũ�� ����
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	ConstructorHelpers::FObjectFinder<UAnimBlueprint> myAnimBP(TEXT("AnimBlueprint'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP'"));
	
	ConstructorHelpers::FObjectFinder<USkeletalMesh> myMesh(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));

	if (myMesh.Succeeded() && myAnimBP.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(myMesh.Object);
		GetMesh()->SetAnimInstanceClass(myAnimBP.Object->GeneratedClass);

		// �޽ø� ȸ���ϰ� ������ ĸ�� ������Ʈ�� �˸°� �����
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

		// ĳ���� �̵� ����
		GetCharacterMovement()->JumpZVelocity = 1450.0f;
		GetCharacterMovement()->GravityScale = 4.5f;

		// ī�޶� �� ����� ( �ݸ����� �ִٸ� �÷��̾� ������ ������� )
		CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
		check(CameraBoom);// isVaild�� ���� ���

		CameraBoom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

		// ī�޶� ĳ���� ���� ���� ���ݸ�ŭ ����´�.
		CameraBoom->TargetArmLength = 500.0f;

		// �÷��̾���� ������
		CameraBoom->AddRelativeLocation(FVector(0.0f, 0.0f, 160.0f));

		// Follow ī�޶� ����
		FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
		check(FollowCamera);

		// �� ���� ī�޶� �����ϰ� ���� ��Ʈ�ѷ� ����� ��ġ�ϵ��� �����Ѵ�.
		FollowCamera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform);

		// ī�޶� �ణ �����ٺ����� �ϱ� ���� ȸ�� ����
		FollowCamera->AddRelativeRotation(FQuat(FRotator(-10.0f, 0.0f, 0.0f)));

		// ���� �Ӽ�
		CharSpeed = 10.0f;

		GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABountyDashCharacter::MyOnComponentBeginOverlap);

		GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ABountyDashCharacter::MyOnComponentEndOverlap);

		// ID 0(�⺻ ��Ʈ�ѷ�)�� �Է� ��������
		AutoPossessPlayer = EAutoReceiveInput::Player0;
	}
}

// Called when the game starts or when spawned
void ABountyDashCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// TargetPoint ������ ���� ����, ���忡 ��ġ�� ��� TargetPoint�� ã�Ƽ� TargetArray�� �־��ش�.
	for (TActorIterator<ATargetPoint> TargetIter(GetWorld()); TargetIter; ++TargetIter)
	{
		TargetArray.Add(*TargetIter);
	}
	
	// ���� ���ʿ� �ִ� TargetPoint ������� ����
	auto SortPred = [](const AActor& A, AActor& B)->bool
	{
		return(A.GetActorLocation().Y < B.GetActorLocation().Y);
	};
	TargetArray.Sort(SortPred);

	// TargetPoint �߿� ��� �ִ� TargetPoint ��ġ ã��
	CurrentLocation = ((TargetArray.Num() / 2) + (TargetArray.Num() % 2) - 1);
}

// Called every frame
void ABountyDashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetArray.Num() > 0)
	{
		FVector targetLoc = TargetArray[CurrentLocation]->GetActorLocation();
		targetLoc.Z = GetActorLocation().Z;
		targetLoc.X = GetActorLocation().X;

		if (targetLoc != GetActorLocation())
		{
			SetActorLocation(FMath::Lerp(GetActorLocation(), targetLoc, CharSpeed * DeltaTime));
		}
	}
}

// Called to bind functionality to input
void ABountyDashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAction("GoRight", IE_Pressed, this, &ABountyDashCharacter::MoveRight);
	InputComponent->BindAction("GoLeft", IE_Pressed, this, &ABountyDashCharacter::MoveLeft);
}

void ABountyDashCharacter::ScoreUp()
{
}

void ABountyDashCharacter::MoveRight()
{
	if ((Controller != nullptr)) {
		if (CurrentLocation < TargetArray.Num() - 1) {
			++CurrentLocation;
		}
	}
}

void ABountyDashCharacter::MoveLeft()
{
	if ((Controller != nullptr)) {
		if (CurrentLocation > 0) {
			--CurrentLocation;
		}
	}
}

void ABountyDashCharacter::MyOnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ABountyDashCharacter::MyOnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

