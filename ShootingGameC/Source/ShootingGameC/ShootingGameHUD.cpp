// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameHUD.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"
#include "ShootingPlayerState.h"
#include "GameFramework/PlayerController.h"

AShootingGameHUD::AShootingGameHUD()
{
}

void AShootingGameHUD::OnUpdateMyDamage_Implementation(float CurrentHealth)
{
}

void AShootingGameHUD::BeginPlay()
{
	check(HudWidgetClass);
	
	HudWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
	HudWidget->AddToViewport();

	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	timerManager.SetTimer(th_BindPlayerState, this, &AShootingGameHUD::BindPlayerState, 0.1f, false);
}

void AShootingGameHUD::BindPlayerState()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
	//	TEXT("Try BindPlayerState"));
	APlayerController* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (pc)
	{
		AShootingPlayerState* ps = Cast<AShootingPlayerState>(pc->PlayerState);
		if (ps)
		{
			ps->Fuc_Dele_UpdateHp_OneParam.BindUFunction(this, FName("OnUpdateMyDamage"));

			OnUpdateMyDamage(ps->GetCurrentHealth());

			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			//	TEXT("Complate BindPlayerState"));
			return;
		}
	}

	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	timerManager.SetTimer(th_BindPlayerState, this, &AShootingGameHUD::BindPlayerState, 0.1f, false);
}
