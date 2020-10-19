#include "ShooterCharacter.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "SimpleShooter/Actors/Gun.h"

AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
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
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageApplied = FMath::Min(Health, DamageApplied);
	Health -= DamageApplied;
	UE_LOG(LogTemp, Warning, TEXT("Health is: %f"), Health);
	return DamageApplied;
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

void AShooterCharacter::Shoot() 
{
	Gun->PullTrigger();
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}