// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ShootingGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAMEC_API AShootingGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	AShootingGameHUD();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> HudWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* HudWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
