#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene Component"));
	SetRootComponent(RootSceneComponent);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	MeshComponent->SetupAttachment(RootSceneComponent);
}

void AGun::BeginPlay()
{
	Super::BeginPlay();
}

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::PullTrigger() 
{
	// Spawn a muzzle flash and sound
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, MeshComponent, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, MeshComponent, TEXT("MuzzleFlashSocket"));

	// Perform our line trace and get the results
	FHitResult OutHit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(OutHit, ShotDirection);

	if (bSuccess) 
	{
		// Spawn impact sound and particles
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, OutHit.ImpactPoint, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, OutHit.ImpactPoint);
		
		// Check that we hit an actor
		AActor* HitActor = OutHit.GetActor();
		if (HitActor != nullptr) {
			// Tell that actor to take damage
			FPointDamageEvent DamageEvent(Damage, OutHit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, GetOwnerController(), this);
		}
	}
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection) 
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) { return false; }

	// Get the Location and Rotation of the player's current view point
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();
	
	// Determine our end location for the line trace
	FVector End = Location + Rotation.Vector() * MaxRange;

	// Make sure to not hit ourselves (the gun) or our owner (the character)
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	// Shoot out our raycast for the player's viewpoint
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

// Get a reference to our controller via GetOwner()
AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) { return nullptr; }
	return OwnerPawn->GetController();
}