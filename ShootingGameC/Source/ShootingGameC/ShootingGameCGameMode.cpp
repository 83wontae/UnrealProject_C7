// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootingGameCGameMode.h"
#include "ShootingGameCCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShootingGameCGameMode::AShootingGameCGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
