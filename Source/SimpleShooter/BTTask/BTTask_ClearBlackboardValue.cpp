#include "BTTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackboardValue::UBTTask_ClearBlackboardValue() 
{
    NodeName = TEXT("Clear Blackboard Value");   
}

EBTNodeResult::Type UBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    FName SelectedKey = GetSelectedBlackboardKey();
    BlackboardComp->ClearValue(SelectedKey);

    return EBTNodeResult::Succeeded;
}