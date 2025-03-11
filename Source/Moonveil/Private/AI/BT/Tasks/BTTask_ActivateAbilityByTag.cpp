// Genesis : The World Creation
#include "AI/BT/Tasks/BTTask_ActivateAbilityByTag.h"
#include "Characters/MoonveilEnemyCharacter.h"
#include "AbilitySystem/MoonveilAbilitySystemComponent.h"

#include "MoonveilDebugHelpers.h"

UBTTask_ActivateAbilityByTag::UBTTask_ActivateAbilityByTag()
{
    NodeName = TEXT("Activate Ability By Tag");

    INIT_TASK_NODE_NOTIFY_FLAGS();
}

FString UBTTask_ActivateAbilityByTag::GetStaticDescription() const
{
    const FString FirstKeyDescription = (TEXT("Ability Tag To Activate: %s"), *AbilityTagToActivate.GetTagName().ToString());

    const FString FinalText = FString::Printf(TEXT("BT_Task_%s\r\n\r\n%s"),
        *UBehaviorTreeTypes::GetShortTypeName(this), *FirstKeyDescription);

    return FinalText;
}

EBTNodeResult::Type UBTTask_ActivateAbilityByTag::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    FEnemyBaseMemory* Memory = CastInstanceNodeMemory<FEnemyBaseMemory>(NodeMemory);

    if (!Memory)
    {
        return EBTNodeResult::Failed;
    }
    
    OnEnemyExecuteTask(OwnerComp, Memory->EnemyCharacterRef.Get());
    
    return EBTNodeResult::Succeeded;
}

void UBTTask_ActivateAbilityByTag::OnEnemyExecuteTask(UBehaviorTreeComponent& OwnerComp, AMoonveilEnemyCharacter* EnemyRef)
{
    if (!EnemyRef) return;
    EnemyRef->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(AbilityTagToActivate.GetSingleTagContainer());
}
