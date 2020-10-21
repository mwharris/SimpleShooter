#include "ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (AIBehavior != nullptr) 
    {
	    RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    
    // Check if we have line of sight to the player
    if (LineOfSightTo(PlayerPawn))
    {
        // Set current and last PlayerLocations if so
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
    }
    else
    {
        // Clear the current PlayerLocation if not
        GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    }
}

bool AShooterAIController::IsDead() const
{
    // Get the pawn and cast to get access to AShooterCharacter::IsDead
    AShooterCharacter* PlayerCharacter = Cast<AShooterCharacter>(GetPawn());
    // Pass on the request to that function on success
    if (PlayerCharacter != nullptr) 
    {
        return PlayerCharacter->IsDead();
    }
    // On fail, then our Controller must be detached from our Pawn,
    // which only happens upon death.  So we must be dead.
    return true; 
}