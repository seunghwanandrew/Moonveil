// Genesis : The World Creation
#include "AI/BT/Tasks/BTTask_TogglingStarfingState.h"
#include "Characters/MoonveilEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FunctionLibrary/MoonveilFunctionLibrary.h"
#include "GamePlayTags/MoonveilGameplayTags.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"

#include "MoonveilDebugHelpers.h"

UBTTask_TogglingStarfingState::UBTTask_TogglingStarfingState()
{
    NodeName = TEXT("Toggling Strafing State");

    INIT_TASK_NODE_NOTIFY_FLAGS();

    bShouldEnableStrafingState = false;
    bShouldChangeWalkMaxSpeed = false;
    StrafingMaxWalkSpeed = 250.0f;
}

void UBTTask_TogglingStarfingState::InitializeFromAsset(UBehaviorTree& Asset)
{
    Super::InitializeFromAsset(Asset);
}

FString UBTTask_TogglingStarfingState::GetStaticDescription() const
{
    const FString FirstKeyDescription = bShouldEnableStrafingState ? FString("Should Enable Strafint State : True") : FString("Should Enable Strafint State : False");
    const FString SecondKeyDescription = bShouldChangeWalkMaxSpeed ? FString("Should Change Walk Max Speed : True") : FString("Should Change Walk Max Speed : False");
    const FString ThridKeyDescription = FString("StrafingMaxWalkSpeed : " + FString::SanitizeFloat(StrafingMaxWalkSpeed));

    const FString FinalText = FString::Printf(TEXT("BT_Task_%s\r\n\r\n%s\r\n%s\r\n%s"),
        *UBehaviorTreeTypes::GetShortTypeName(this), *FirstKeyDescription, *SecondKeyDescription, *ThridKeyDescription);

    return FinalText;
}

EBTNodeResult::Type UBTTask_TogglingStarfingState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    FEnemyBaseMemory* Memory = CastInstanceNodeMemory<FEnemyBaseMemory>(NodeMemory);

    if (!Memory || !Memory->IsValid())
    {
        return EBTNodeResult::Failed;
    }

    OnEnemyExecuteTask(OwnerComp, Memory->EnemyCharacterRef.Get());

    return EBTNodeResult::Succeeded;
}

void UBTTask_TogglingStarfingState::OnEnemyExecuteTask(UBehaviorTreeComponent& OwnerComp, AMoonveilEnemyCharacter* EnemyRef)
{
 
    if (!EnemyRef) return;

    UCharacterMovementComponent* EnemyMovement = EnemyRef->GetCharacterMovement();

    if (bShouldEnableStrafingState)
    {
        EnemyMovement->bOrientRotationToMovement = false;

        if (bShouldChangeWalkMaxSpeed)
        {
            EnemyMovement->MaxWalkSpeed = StrafingMaxWalkSpeed;
        }

        UMoonveilFunctionLibrary::AddGameplayTagToActorIfNone(EnemyRef, FMoonveilGameplayTags::Enemy_Status_Strafing);
    }

    else
    {
        EnemyMovement->bOrientRotationToMovement = true;

        float DefaultMaxWalkSpeed = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(FName(TEXT("DefaultMaxWalkSpeed")));
        
        if (DefaultMaxWalkSpeed != EnemyMovement->MaxWalkSpeed)
        {
            EnemyMovement->MaxWalkSpeed = DefaultMaxWalkSpeed;
        }

        UMoonveilFunctionLibrary::RemoveGameplayTagFromActorIfHas(EnemyRef, FMoonveilGameplayTags::Enemy_Status_Strafing);
    }
}
