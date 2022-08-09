// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BountyDash.h"
#include "GameFramework/HUD.h"
#include "BountyDashHUD.generated.h"

/**
 * 
 */
UCLASS()
class BOUNTYDASH_API ABountyDashHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ABountyDashHUD();

	UPROPERTY()
	UFont* HUDFont;

	virtual void DrawHUD() override;
};
