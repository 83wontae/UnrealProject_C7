// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BountyDash.h"
#include "PowerUpObject.h"
#include "GameFramework/Character.h"
#include "BountyDashCharacter.generated.h"

UCLASS()
class BOUNTYDASH_API ABountyDashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABountyDashCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// 이동 방향 배열
	UPROPERTY(EditAnywhere, Category = Logic)
	TArray<class ATargetPoint*> TargetArray;

	// 캐릭터 줄 바꿈 속도
	UPROPERTY(EditAnywhere, Category = Logic)
	float CharSpeed;

	// 충돌 사운드를 위한 오디오 컴포넌트
	UPROPERTY(EditAnywhere, Category = Sound)
	UAudioComponent* hitObstacleSound;

	// 코인 획득 사운드를 위해나 오디오 컴포넌트
	UPROPERTY(EditAnywhere, Category = Sound)
	UAudioComponent* dingSound;

protected:
	// 플레이어와 카메라 간의 거리를 유지하기 위한 카메라 붐
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	// 타겟 뷰로 사용할 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	// 플레이어 점수
	UPROPERTY(BlueprintReadOnly)
	int32 Score;

	// Smash 시간
	UPROPERTY(EditAnywhere, Category = PowerUps)
	float SmashTime;

	// Magnet 시간
	UPROPERTY(EditAnywhere, Category = PowerUps)
	float MagnetTime;

	// Magnet 거리
	UPROPERTY(EditAnywhere, Category = PowerUps)
	float MagnetReach;

	// 킬 포인트
	float KillPoint;

private:
	//캐릭터 서있는 위치 데이터
	short CurrentLocation;
	FVector DesiredLocation;
	bool bBeingPushed;

	//파위 업 속성
	bool CanSmash;
	bool CanMagnet;

public:
	void ScoreUp();
	void PowerUp(EPowerUp Type);
	int GetScore();

protected:
	// 플레이어 좌우의 타깃 위치 이동을 조정한다
	void MoveRight();
	void MoveLeft();
	// 컴포넌트 콜리전 캡슐에 사용되는 오버랩 함수
	UFUNCTION()
	void MyOnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void MyOnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void StopSmash();

	UFUNCTION()
	void StopMagnet();

	void CoinMagnet();

	UFUNCTION()
	void Reset();
};
