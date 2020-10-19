#include "ShooterAIController.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    APawn* OurPawn = GetPawn();
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (AIBehavior != nullptr) 
    {
	    RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), OurPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    /*
    // Check if we have line of sight to the player
    if (LineOfSightTo(PlayerPawn))
    {
        // If so, aim and move towards them
        SetFocus(PlayerPawn, EAIFocusPriority::Gameplay);
        MoveToActor(PlayerPawn, AcceptanceRadius, false);
    }
    else
    {
        // If not, ignore them
        ClearFocus(EAIFocusPriority::Gameplay);
        StopMovement();
    }
    */
}