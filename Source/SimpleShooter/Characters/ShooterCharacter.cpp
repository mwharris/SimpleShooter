#include "ShooterCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "SimpleShooter/Actors/Gun.h"
#include "SimpleShooter/SimpleShooterGameModeBase.h"

AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	// Get a reference to our GameMode
	GameModeRef = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
	//Default our starting health
	Health = MaxHealth;
	// Hide the gun that is part of the Wraith skeletal mesh
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	// Spawn our BP_Gun class
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	// Attach our gun to WeaponSocket
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	// Set the owner for future purposes
	Gun->SetOwner(this);
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
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AShooterCharacter::Shoot);
}

void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) 
{
	// Call the super take damage in case there are some calculations there
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	// Subtract our total applied damage
	Health -= FMath::Min(Health, DamageApplied);
	// Cleanup if we died
	if (IsDead())
	{
		// Tell the GameMode we killed a pawn
		if (GameModeRef != nullptr) 
		{
			GameModeRef->PawnKilled(this);
		}
		// Detach from the player controller to disable any input
		DetachFromControllerPendingDestroy();
		// Disable all collisions
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	return DamageApplied;
}

void AShooterCharacter::Shoot() 
{
	Gun->PullTrigger();
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

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}