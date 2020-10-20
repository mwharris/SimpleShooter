#include "BTService_PlayerLocationIfSeen.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen() 
{
    NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    // Always make sure to call super's tick function
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    // Get a reference to our AIController
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController == nullptr) 
    {
        return;
    }

    // Get a reference to the player pawn
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn == nullptr) 
    {
        return;
    }

    // Check if our AIController has LineOfSightTo our PlayerPawn
    if (AIController->LineOfSightTo(PlayerPawn)) 
    {
        // Set the player's location if so
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
    }
    else 
    {
        // Otherwise clear out the player's location
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}