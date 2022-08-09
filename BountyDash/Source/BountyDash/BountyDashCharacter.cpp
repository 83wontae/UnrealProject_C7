// Fill out your copyright notice in the Description page of Project Settings.


#include "BountyDashCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/TargetPoint.h"
#include "EngineUtils.h"
#include "Obstacle.h"
#include "BountyDashGameModeBase.h"
#include "Coin.h"
#include "DestructibleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Floor.h"
#include "BountyDashParticle.h"

// Sets default values
ABountyDashCharacter::ABountyDashCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 콜리전 캡슐 크기 조절
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	ConstructorHelpers::FObjectFinder<UAnimBlueprint> myAnimBP(TEXT("AnimBlueprint'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP'"));
	
	ConstructorHelpers::FObjectFinder<USkeletalMesh> myMesh(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));

	if (myMesh.Succeeded() && myAnimBP.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(myMesh.Object);
		GetMesh()->SetAnimInstanceClass(myAnimBP.Object->GeneratedClass);

		// 메시를 회전하고 움직여 캡슐 컴포넌트에 알맞게 맞춘다
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

		// 캐릭터 이동 구성
		GetCharacterMovement()->JumpZVelocity = 1450.0f;
		GetCharacterMovement()->GravityScale = 4.5f;

		// 카메라 붐 만들기 ( 콜리전이 있다면 플레이어 쪽으로 끌어당긴다 )
		CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
		check(CameraBoom);// isVaild와 같은 기능

		CameraBoom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

		// 카메라가 캐릭터 뒤의 일정 간격만큼 따라온다.
		CameraBoom->TargetArmLength = 500.0f;

		// 플레이어로의 오프셋
		CameraBoom->AddRelativeLocation(FVector(0.0f, 0.0f, 160.0f));

		// Follow 카메라 생성
		FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
		check(FollowCamera);

		// 붐 끝에 카메라를 연결하고 붐이 컨트롤러 방향과 일치하도록 조정한다.
		FollowCamera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform);

		// 카메라가 약간 내려다보도록 하기 위한 회전 변경
		FollowCamera->AddRelativeRotation(FQuat(FRotator(-10.0f, 0.0f, 0.0f)));

		// 게임 속성
		CharSpeed = 10.0f;
		SmashTime = 10.0f;
		MagnetTime = 10.0f;
		MagnetReach = 1000.0f;

		GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABountyDashCharacter::MyOnComponentBeginOverlap);

		GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ABountyDashCharacter::MyOnComponentEndOverlap);

		// ID 0(기본 컨트롤러)의 입력 가져오기
		AutoPossessPlayer = EAutoReceiveInput::Player0;
	}
}

// Called when the game starts or when spawned
void ABountyDashCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// TargetPoint 움직일 라인 갯수, 월드에 배치된 모든 TargetPoint를 찾아서 TargetArray에 넣어준다.
	for (TActorIterator<ATargetPoint> TargetIter(GetWorld()); TargetIter; ++TargetIter)
	{
		TargetArray.Add(*TargetIter);
	}
	
	// 가장 왼쪽에 있는 TargetPoint 순서대로 정렬
	auto SortPred = [](const AActor& A, AActor& B)->bool
	{
		return(A.GetActorLocation().Y < B.GetActorLocation().Y);
	};
	TargetArray.Sort(SortPred);

	// TargetPoint 중에 가운데 있는 TargetPoint 위치 찾기
	CurrentLocation = ((TargetArray.Num() / 2) + (TargetArray.Num() % 2) - 1);

	// 킬포인트 위치 설정
	for (TActorIterator<AFloor> TargetIter(GetWorld()); TargetIter; ++TargetIter)
	{
		KillPoint = TargetIter->GetKillPoint();
	}
}

// Called every frame
void ABountyDashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 라인 사이를 부드럽게 이동
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

	// 장애물에 붙이쳤을때 대상이 bBeingPushed 라면 캐릭터를 뒤로 밀어낸다
	if (bBeingPushed)
	{
		float movespeed = GetCustomGameMode<ABountyDashGameModeBase>(GetWorld())->GetInvGameSpeed();
		AddActorLocalOffset(FVector(movespeed, 0.0f, 0.0f));
	}

	// 코인을 자석처럼 끌어 당긴다.
	if (CanMagnet)
	{
		CoinMagnet();
	}

	// KillPoint에 다다르면 GameOver 처리
	if (GetActorLocation().X < KillPoint)
	{
		GetCustomGameMode<ABountyDashGameModeBase>(GetWorld())->GameOver();
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
	// bExecuteWhenPaused - 게임이 일시 중지된 상태라도 인풋 액션을 수행할수 있게 설정
	InputComponent->BindAction("Reset", IE_Pressed, this, &ABountyDashCharacter::Reset).bExecuteWhenPaused = true;
}

void ABountyDashCharacter::ScoreUp()
{
	Score++;
	GetCustomGameMode<ABountyDashGameModeBase>(GetWorld())->CharScoreUp(Score);
}

void ABountyDashCharacter::PowerUp(EPowerUp Type)
{
	switch (Type)
	{
	case EPowerUp::SPEED: 
	{
		GetCustomGameMode<ABountyDashGameModeBase>(GetWorld())->ReduceGameSpeed();
		break; 
	}
	case EPowerUp::SMASH:
	{
		CanSmash = true;
		FTimerHandle newTimer;
		GetWorld()->GetTimerManager().SetTimer(newTimer, this, &ABountyDashCharacter::StopSmash, SmashTime, false);
		break;
	}
	case EPowerUp::MAGNET:
	{
		CanMagnet = true;
		FTimerHandle newTimer;
		GetWorld()->GetTimerManager().SetTimer(newTimer, this, &ABountyDashCharacter::StopMagnet, MagnetTime, false);
		break;
	}
	default:
		break;
	}
}

int ABountyDashCharacter::GetScore()
{
	return Score;
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
	if (OtherActor->GetClass()->IsChildOf(AObstacle::StaticClass()))
	{
		// 오브젝트를 부시거나 캐릭터 밀어내기 bBeingPushed 설정
		FVector vecBetween = OtherActor->GetActorLocation() - GetActorLocation();
		float AngleBetween = FMath::Acos(FVector::DotProduct(vecBetween.GetSafeNormal(), GetActorForwardVector().GetSafeNormal()));

		AngleBetween *= (180 / PI);

		if (AngleBetween < 60.0f)
		{
			AObstacle* pObs = Cast<AObstacle>(OtherActor);
			if (pObs && CanSmash)
			{
				pObs->GetDestructable()->ApplyRadiusDamage(10000, GetActorLocation(), 10000, 10000, true);

				// 파괴 이펙트 출력
				ABountyDashParticle* particleSys = GetWorld()->SpawnActor<ABountyDashParticle>(ABountyDashParticle::StaticClass(), GetTransform());
				particleSys->SetKillPoint(KillPoint);
			}
			else
			{
				bBeingPushed = true;
			}
		}
	}
}

void ABountyDashCharacter::MyOnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetClass()->IsChildOf(AObstacle::StaticClass()))
	{
		bBeingPushed = false;
	}
}

void ABountyDashCharacter::StopSmash()
{
	CanMagnet = false;
}

void ABountyDashCharacter::StopMagnet()
{
	CanSmash = false;
}

void ABountyDashCharacter::CoinMagnet()
{
	for (TActorIterator<ACoin> coinIter(GetWorld()); coinIter; ++coinIter)
	{
		FVector between = GetActorLocation() - coinIter->GetActorLocation();
		if (FMath::Abs(between.Size()) < MagnetReach)
		{
			FVector CoinPos = FMath::Lerp((*coinIter)->GetActorLocation(), GetActorLocation(), 0.2);
			(*coinIter)->SetActorLocation(CoinPos);
			(*coinIter)->BeingPulled = true;
		}
	}
}

void ABountyDashCharacter::Reset()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("BountyDashMap"));
}

