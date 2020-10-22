#include "BTService_PlayerLocation.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerLocation::UBTService_PlayerLocation() 
{
    NodeName = TEXT("Update Last Known Location");
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    // Get a reference to the player pawn
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn == nullptr) 
    {
        return;
    }

    // Set the LastKnownPlayerLocation key to the player pawn location
    OwnerComp.GetBlackboardComponent()->SetValueAsObject(
        GetSelectedBlackboardKey(), 
        PlayerPawn
    );
}