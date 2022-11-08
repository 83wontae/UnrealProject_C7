// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShootingGameCCharacter.generated.h"

UCLASS(config=Game)
class AShootingGameCCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AShootingGameCCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

private:
	UPROPERTY(Replicated)
	AActor* EquippedWeapon;

	UPROPERTY(Replicated)
	float PawnDiraction;

	UPROPERTY(Replicated)
	float PawnControlPitch;

	bool IsRagDoll;

protected:
	FTimerHandle th_BindPlayerState;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void DoRagdoll();

	UFUNCTION(BlueprintCallable)
	void DoGetup();

	UFUNCTION(BlueprintCallable)
	AActor* SetEquippedWeapon(AActor* Weapon);

	UFUNCTION(BlueprintPure)
	FORCEINLINE AActor* GetEquippedWeapon() const { return EquippedWeapon; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetPawnDiraction() const { return PawnDiraction; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetPawnControlPitch() const { return PawnControlPitch; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool GetIsRagDoll() const { return IsRagDoll; }

	UFUNCTION(BlueprintNativeEvent)
	void OnUpdateDamage(float CurrentHealth);

	void OnUpdateDamage_Implementation(float CurrentHealth);

	UFUNCTION(BlueprintCallable)
	void OnNotifyShoot();

	UFUNCTION(BlueprintCallable)
	void OnNotifyReload();

private:
	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerUpdateDir(const float Diraction, const float ControlPitch);

	void BindPlayerState();

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void PressTestKeyF();

	void PressShootKey();

	void ReleasedShootKey();

	void PressReloadKey();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


};

