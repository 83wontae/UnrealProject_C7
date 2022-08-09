// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BountyDashGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BOUNTYDASH_API ABountyDashGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ABountyDashGameModeBase();

	void CharScoreUp(unsigned int charScore);

	UFUNCTION()
	float GetInvGameSpeed();

	UFUNCTION()
	float GetGameSpeed();

	UFUNCTION()
	int32 GetGameLevel();

	void ReduceGameSpeed();

	float GetRunTime();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	bool GetGameOver();

	UFUNCTION()
	void GameOver();

	UFUNCTION()
	void SetGamePaused(bool gamePaused);

private:
	UPROPERTY()
	float gameSpeed;

	UPROPERTY()
	int32 gameLevel;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 numCoinsForSpeedIncrease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float gameSpeedIncrease;

	UPROPERTY()
	float RunTime;

	UPROPERTY()
	bool bGameOver;

	UPROPERTY()
	bool startGameOverCount;

	UPROPERTY()
	float timeTillGameOver;

	UPROPERTY()
	float gameOverTimer;
};
