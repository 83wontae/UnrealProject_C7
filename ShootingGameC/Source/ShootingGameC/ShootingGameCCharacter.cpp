// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootingGameCCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "WeaponInterface.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "ShootingPlayerState.h"

//////////////////////////////////////////////////////////////////////////
// AShootingGameCCharacter

AShootingGameCCharacter::AShootingGameCCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void AShootingGameCCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShootingGameCCharacter, PawnDiraction);
	DOREPLIFETIME(AShootingGameCCharacter, PawnControlPitch);
	DOREPLIFETIME(AShootingGameCCharacter, EquippedWeapon);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AShootingGameCCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShootingGameCCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShootingGameCCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AShootingGameCCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AShootingGameCCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AShootingGameCCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AShootingGameCCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AShootingGameCCharacter::OnResetVR);

	// TestKeyF
	PlayerInputComponent->BindAction("TestKeyF", IE_Pressed, this, &AShootingGameCCharacter::PressTestKeyF);

	// ShootKey
	PlayerInputComponent->BindAction("ShootKey", IE_Pressed, this, &AShootingGameCCharacter::PressShootKey);
}


void AShootingGameCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Controller == UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		PawnDiraction = GetMesh()->GetAnimInstance()->CalculateDirection(GetVelocity(), GetActorRotation());
		PawnControlPitch = GetControlRotation().Pitch;

		if (Controller->HasAuthority() == false)
		{
			ServerUpdateDir(PawnDiraction, PawnControlPitch);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Send ServerUpdateDir")));
		}
	}

	if (IsRagDoll)
	{
		// 월드->상대
		// FVector relativeLoc = GetTransform().InverseTransformPosition(someWorldPosition);

		// 상대->월드
		FVector vAttach = GetMesh()->GetSocketLocation("pelvis") + FVector(0.0f, 0.0f, 50.0f);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("vAttach Location=(%f,%f,%f)"), vAttach.X, vAttach.Y, vAttach.Z));
		
		SetActorLocation(vAttach);
	}
}

float AShootingGameCCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float trueDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
	//	FString::Printf(TEXT("TakeDamage Damage=%f EventInstigator=%s"), trueDamage, *EventInstigator->GetName()));

	AShootingPlayerState* ps = Cast<AShootingPlayerState>(GetPlayerState());
	if (ps)
	{
		ps->AddDamage(trueDamage);
	}

	return 0.0f;
}

void AShootingGameCCharacter::BeginPlay()
{
	Super::BeginPlay();

	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	timerManager.SetTimer(th_BindPlayerState, this, &AShootingGameCCharacter::BindPlayerState, 0.1f, false);
}

void AShootingGameCCharacter::DoRagdoll()
{
	IsRagDoll = true;

	GetMesh()->SetSimulatePhysics(true);
}

void AShootingGameCCharacter::DoGetup()
{
	IsRagDoll = false;

	GetMesh()->SetSimulatePhysics(false);

	GetMesh()->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	FVector loc = { 0.0f,0.0f,-97.0f };
	FRotator Rot = { 0.0f,-90.0f, 0.0f };
	GetMesh()->SetRelativeLocationAndRotation(loc, Rot);
}

bool AShootingGameCCharacter::ServerUpdateDir_Validate(const float Diraction, const float ControlPitch)
{
	return true;
}

void AShootingGameCCharacter::ServerUpdateDir_Implementation(const float Diraction, const float ControlPitch)
{
	PawnDiraction = Diraction;
	PawnControlPitch = ControlPitch;

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
	//	FString::Printf(TEXT("ServerUpdateDir_Implementation Diraction=%f, ControlPitch=%f"), PawnDiraction, PawnControlPitch));
}

void AShootingGameCCharacter::OnUpdateDamage_Implementation(float CurrentHealth)
{
	if (CurrentHealth <= 0)
		DoRagdoll();
}

void AShootingGameCCharacter::BindPlayerState()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
		TEXT("Try BindPlayerState"));
	AShootingPlayerState* ps = Cast<AShootingPlayerState>(GetPlayerState());
	if (ps)
	{
		ps->Fuc_Dele_UpdateHp_OneParam.BindUFunction(this, FName("OnUpdateDamage"));

		OnUpdateDamage(ps->GetCurrentHealth());

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			TEXT("Complate BindPlayerState"));
		return;
	}

	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	timerManager.SetTimer(th_BindPlayerState, this, &AShootingGameCCharacter::BindPlayerState, 0.1f, false);
}

void AShootingGameCCharacter::OnResetVR()
{
	// If ShootingGameC is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in ShootingGameC.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AShootingGameCCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AShootingGameCCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AShootingGameCCharacter::PressTestKeyF()
{
	AShootingPlayerState* ps = Cast<AShootingPlayerState>(GetPlayerState());
	if (ps)
	{
		ps->AddDamage(10.0f);
	}

	if (IsRagDoll)
	{
		DoGetup();
	}
	else
	{
		DoRagdoll();
	}
}

void AShootingGameCCharacter::PressShootKey()
{
	IWeaponInterface* InterfaceObj = Cast<IWeaponInterface>(EquippedWeapon);

	if (InterfaceObj)
	{
		InterfaceObj->Execute_PressKey_F(EquippedWeapon);
	}
}

void AShootingGameCCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AShootingGameCCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AShootingGameCCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AShootingGameCCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
