#include "ShooterCharacter.h"
#include "Components/InputComponent.h"

AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Keyboard movement axis bindings
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &AShooterCharacter::MoveRight);

	// Mouse look axis bindings
	PlayerInputComponent->BindAxis(TEXT("MouseLookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MouseLookRight"), this, &APawn::AddControllerYawInput);

	// Controller look axis bindings
	PlayerInputComponent->BindAxis(TEXT("ControllerLookUp"), this, &AShooterCharacter::ControllerLookUp);
	PlayerInputComponent->BindAxis(TEXT("ControllerLookRight"), this, &AShooterCharacter::ControllerLookRight);
	
	// Action bindings
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
}

void AShooterCharacter::MoveForward(float AxisValue) 
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue) 
{
	AddMovementInput(GetActorRightVector() * AxisValue);	
}

void AShooterCharacter::ControllerLookUp(float AxisValue) 
{
	AddControllerPitchInput(AxisValue * RotationSpeed * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::ControllerLookRight(float AxisValue) 
{
	AddControllerYawInput(AxisValue * RotationSpeed * GetWorld()->GetDeltaSeconds());
}