// Genesis : The World Creation
#include "AI/BT/Tasks/BTTask_EnemyBase.h"
#include "AIController.h"
#include "Characters/MoonveilEnemyCharacter.h"

UBTTask_EnemyBase::UBTTask_EnemyBase()
{
    bNotifyTick = true;
    bNotifyTaskFinished = true;
    bCreateNodeInstance = false;

    NodeName = TEXT("Enemy Base");

    INIT_TASK_NODE_NOTIFY_FLAGS();
}

void UBTTask_EnemyBase::InitializeFromAsset(UBehaviorTree& Asset)
{
    Super::InitializeFromAsset(Asset);
}

FString UBTTask_EnemyBase::GetStaticDescription() const
{
    return UBehaviorTreeTypes::GetShortTypeName(this);
}

uint16 UBTTask_EnemyBase::GetInstanceMemorySize() const
{
    return sizeof(FEnemyBaseMemory);
}

EBTNodeResult::Type UBTTask_EnemyBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    FEnemyBaseMemory* Memory = CastInstanceNodeMemory<FEnemyBaseMemory>(NodeMemory);

    check(Memory);

    if (!Memory)
    {
        return EBTNodeResult::Failed;
    }

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    AMoonveilEnemyCharacter* EnemyCharacter = Cast<AMoonveilEnemyCharacter>(AIController->GetPawn());
    if (!EnemyCharacter)
    {
        return EBTNodeResult::Failed;
    }

    Memory->EnemyCharacterRef = EnemyCharacter;

    return EBTNodeResult::InProgress;
}

void UBTTask_EnemyBase::OnEnemyExecuteTask(UBehaviorTreeComponent& OwnerComp, AMoonveilEnemyCharacter* EnemyRef)
{
}
