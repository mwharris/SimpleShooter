#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    // Show either the Win or Lose screen
    CreateEndScreenWidget(bIsWinner);
    // Create a timer to restart the level after a delay
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

// Create either the Win or Lose screen widget depending on bIsWinner
void AShooterPlayerController::CreateEndScreenWidget(bool bIsWinner) 
{
    if (bIsWinner) 
    {
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass, TEXT("Win Screen"));
        if (WinScreen != nullptr) 
        {
            WinScreen->AddToViewport();
        }
    }
    else
    {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass, TEXT("Lose Screen"));
        if (LoseScreen != nullptr) 
        {
            LoseScreen->AddToViewport();
        }
    }
}