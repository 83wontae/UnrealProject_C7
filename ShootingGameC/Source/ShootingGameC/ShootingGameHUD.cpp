// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameHUD.h"
#include "Blueprint/UserWidget.h"

AShootingGameHUD::AShootingGameHUD()
{
}

void AShootingGameHUD::BeginPlay()
{
	check(HudWidgetClass);
	
	HudWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
	HudWidget->AddToViewport();
}
