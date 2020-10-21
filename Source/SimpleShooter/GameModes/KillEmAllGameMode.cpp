#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/AI/ShooterAIController.h"

// Called by ShooterCharacter upon death for win/lose condition handling
void AKillEmAllGameMode::PawnKilled(APawn* KilledPawn) 
{
    Super::PawnKilled(KilledPawn);
    // Check if the pawn killed is the player; end the game
    APlayerController* PlayerController = Cast<APlayerController>(KilledPawn->GetController());
    if (PlayerController != nullptr) 
    {
        EndGame(false);
    }
    // End the game if all enemies have been killed
    else if (CheckWinCondition()) 
    {
        EndGame(true);
    }
}

// Returns true if all AShooterAIController in the level are dead 
bool AKillEmAllGameMode::CheckWinCondition() const
{
    for(AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
    {
        if (!Controller->IsDead()) 
        {
            return false;
        }
    }
    return true;
}

// Notifies all Controllers that the game has ended
void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner) 
{
    // Loop over every Controller in the World
    for(AController* Controller : TActorRange<AController>(GetWorld()))
    {
        // Call each Controller::GameHasEnded.
        // Pass the result based on if the Controller is the player or AI.
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}