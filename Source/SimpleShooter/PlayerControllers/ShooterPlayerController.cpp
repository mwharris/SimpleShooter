#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "SimpleShooter/UserWidget/HUDUserWidget.h"
#include "TimerManager.h"

void AShooterPlayerController::BeginPlay() 
{
    // Create our HUD and add to the viewport
    HUD = CreateWidget(this, HUDClass, TEXT("HUD"));
    if (HUD != nullptr)
    {
        HUD->AddToViewport();
    }
}

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    // Hide the HUD
    if (HUD != nullptr) 
    {
        HUD->RemoveFromViewport();
    }
    // Show either the Win or Lose screen
    CreateEndScreenWidget(bIsWinner);
    // Create a timer to restart the level after a delay
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

void AShooterPlayerController::UpdateHUDHealth(float NewHealth) 
{
    UHUDUserWidget* ShooterHUD = Cast<UHUDUserWidget>(HUD);
    if (ShooterHUD != nullptr) 
    {
        ShooterHUD->UpdateHealthUI(NewHealth);
    }
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