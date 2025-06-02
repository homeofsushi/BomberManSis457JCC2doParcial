// Copyright Epic Games, Inc. All Rights Reserved.

#include "BomberManSIS457JCCCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Coin.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// ABomberManSIS457JCCCharacter

ABomberManSIS457JCCCharacter::ABomberManSIS457JCCCharacter()
{
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
	GetCharacterMovement()->JumpZVelocity = 300.f;
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

//////////////////////////////////////////////////////////////////////////
// Input

void ABomberManSIS457JCCCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABomberManSIS457JCCCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABomberManSIS457JCCCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABomberManSIS457JCCCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABomberManSIS457JCCCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ABomberManSIS457JCCCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ABomberManSIS457JCCCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ABomberManSIS457JCCCharacter::OnResetVR);
	PlayerInputComponent->BindAction("ReturnCoins", IE_Pressed, this, &ABomberManSIS457JCCCharacter::ReturnCoins);
}


void ABomberManSIS457JCCCharacter::OnResetVR()
{
	// If BomberManSIS457JCC is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in BomberManSIS457JCC.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ABomberManSIS457JCCCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ABomberManSIS457JCCCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ABomberManSIS457JCCCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABomberManSIS457JCCCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABomberManSIS457JCCCharacter::MoveForward(float Value)
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

void ABomberManSIS457JCCCharacter::MoveRight(float Value)
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

void ABomberManSIS457JCCCharacter::CollectCoin(ACoin* Coin)
{
	if (!Coin) return;

	// Si ya tiene una moneda de ese tipo, no recoge otra
	if (CollectedCoins.Contains(Coin->CoinType))
	{
		UE_LOG(LogTemp, Warning, TEXT("Ya tienes una moneda de este tipo"));
		return;
	}

	CollectedCoins.Add(Coin->CoinType, Coin);

	// Oculta la moneda y desactiva colisi�n
	Coin->SetActorHiddenInGame(true);
	Coin->SetActorEnableCollision(false);

	UE_LOG(LogTemp, Warning, TEXT("Moneda guardada XD"));
}
void ABomberManSIS457JCCCharacter::ReturnCoins()
{
	FVector BaseLocation = GetActorLocation();
	float Offset = 250.0f;
	int Index = 0;
	for (auto& Elem : CollectedCoins)
	{
		ACoin* Coin = Elem.Value;
		if (Coin)
		{
			Coin->SetActorHiddenInGame(false);
			Coin->SetActorEnableCollision(true);
			Coin->SetActorLocation(BaseLocation + FVector((Index - CollectedCoins.Num() / 2) * Offset, 0, 0));
		}
		Index++;
	}
	CollectedCoins.Empty();
}
