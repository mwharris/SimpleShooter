#include "KillEmAllGameMode.h"
#include "Kismet/GameplayStatics.h"

void AKillEmAllGameMode::PawnKilled(APawn* KilledPawn) 
{
    Super::PawnKilled(KilledPawn);

    APlayerController* PlayerController = Cast<APlayerController>(KilledPawn->GetController());
    if (PlayerController != nullptr) 
    {
        PlayerController->GameHasEnded(nullptr, false);
    }
}