// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameHUD.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"
#include "ShootingPlayerState.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"

AShootingGameHUD::AShootingGameHUD()
{
}

void AShootingGameHUD::OnUpdateMyDamage_Implementation(float CurrentHealth)
{
}

void AShootingGameHUD::OnUpdateAmmo_Implementation(int CurrentAmmo)
{
}

void AShootingGameHUD::BeginPlay()
{
	Super::BeginPlay();

	check(HudWidgetClass);
	
	HudWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
	HudWidget->AddToViewport();

	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	timerManager.SetTimer(th_BindPlayerState, this, &AShootingGameHUD::BindPlayerState, 1.1f, false);
}

void AShootingGameHUD::BindPlayerState()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
	//	TEXT("Try BindPlayerState"));
	//ACharacter* playerchar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if (IsValid(pc) && pc->PlayerState != nullptr)
	{
		AShootingPlayerState* ps = Cast<AShootingPlayerState>(pc->PlayerState);
		if (IsValid(ps))
		{
			ps->Fuc_Dele_UpdateHp_OneParam.AddUFunction(this, FName("OnUpdateMyDamage"));

			OnUpdateMyDamage(ps->GetCurrentHealth());

			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
				FString::Printf(TEXT("%d Complate BindPlayerState"), *ps->GetName()));
			return;
		}
	}

	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	timerManager.SetTimer(th_BindPlayerState, this, &AShootingGameHUD::BindPlayerState, 0.1f, false);
}
