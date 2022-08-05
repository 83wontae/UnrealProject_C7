// Copyright Epic Games, Inc. All Rights Reserved.


#include "BountyDashGameModeBase.h"
#include "BountyDashCharacter.h"

ABountyDashGameModeBase::ABountyDashGameModeBase()
{
	// ABountyDashCharacter를 위한 기본 폰 클래스 설정
	DefaultPawnClass = ABountyDashCharacter::StaticClass();

	numCoinsForSpeedIncrease = 5;
	gameSpeed = 10.0f;
	gameSpeedIncrease = 5.0f;
	gameLevel = 1;
}

void ABountyDashGameModeBase::CharScoreUp(unsigned int charScore)
{
	if (charScore != 0 && charScore % numCoinsForSpeedIncrease == 0)
	{
		gameSpeed += gameSpeedIncrease;
		gameLevel++;
	}
}

float ABountyDashGameModeBase::GetInvGameSpeed()
{
	return -gameSpeed;
}

float ABountyDashGameModeBase::GetGameSpeed()
{
	return gameSpeed;
}

int32 ABountyDashGameModeBase::GetGameLevel()
{
	return gameLevel;
}
