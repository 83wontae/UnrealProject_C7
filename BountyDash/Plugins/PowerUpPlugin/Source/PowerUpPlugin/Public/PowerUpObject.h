// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PowerUpObject.generated.h"

enum class EPowerUp : uint8
{
	SPEED = 1 UMETA(DisplayName = "Speed"),
	SMASH = 2 UMETA(DisplayName = "Smash"),
	MAGNET = 3 UMETA(DisplayName = "Magent")
};

/**
 * 
 */
UCLASS()
class POWERUPPLUGIN_API UPowerUpObject : public UObject
{
	GENERATED_BODY()
	
public:
	UPowerUpObject(const FObjectInitializer& ObjectInitializer);

	EPowerUp GetType();

private:
	EPowerUp Type;
};
