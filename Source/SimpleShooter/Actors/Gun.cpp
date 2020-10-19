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
	// Spawn a muzzle flash
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, MeshComponent, TEXT("MuzzleFlashSocket"));
	
	// Get a reference to our controller view GetOwner()
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) { return; }
	AController* OwnerController = OwnerPawn->GetController();
	if (!OwnerController) { return; }

	// Get the Location and Rotation of the player's current view point
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	
	// Shoot our our raycast for the player's viewpoint
	FHitResult OutHit;
	FVector End = Location + Rotation.Vector() * MaxRange;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(OutHit, Location, End, ECollisionChannel::ECC_GameTraceChannel1);

	if (bSuccess) 
	{
		FVector ShotDirection = -Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, OutHit.ImpactPoint, ShotDirection.Rotation());
		
		// Check that we hit an actor
		AActor* HitActor = OutHit.GetActor();
		if (HitActor != nullptr) {
			// Tell that actor to take damage
			FPointDamageEvent DamageEvent(Damage, OutHit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}

		// DrawDebugLine(GetWorld(), Location, End, FColor::Yellow, true);
		// DrawDebugPoint(GetWorld(), OutHit.ImpactPoint, 20.f, FColor::Red, true);
	}
}