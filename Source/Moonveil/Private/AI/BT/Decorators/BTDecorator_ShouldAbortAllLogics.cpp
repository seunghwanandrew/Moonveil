// Genesis : The World Creation
#include "AI/BT/Decorators/BTDecorator_ShouldAbortAllLogics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FunctionLibrary/MoonveilFunctionLibrary.h"
#include "GamePlayTags/MoonveilGameplayTags.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"

UBTDecorator_ShouldAbortAllLogics::UBTDecorator_ShouldAbortAllLogics()
{
	NodeName = "Should Stop All Logic?";

	INIT_DECORATOR_NODE_NOTIFY_FLAGS();

	InTargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, InTargetActorKey), AActor::StaticClass());
	InDistToTargetKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, InDistToTargetKey));
}

void UBTDecorator_ShouldAbortAllLogics::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		InTargetActorKey.ResolveSelectedKey(*BBAsset);
		InDistToTargetKey.ResolveSelectedKey(*BBAsset);
	}
}

FString UBTDecorator_ShouldAbortAllLogics::GetStaticDescription() const
{
	FString FlowAbortDesc;
	if (FlowAbortMode != EBTFlowAbortMode::None)
	{
		FlowAbortDesc = FString::Printf(TEXT("( aborts %s )"), *UBehaviorTreeTypes::DescribeFlowAbortMode(FlowAbortMode).ToLower());
	}

	FString FirstDescription = FString("In Target Actor Key:" + InTargetActorKey.SelectedKeyName.ToString());
	FString SecondDescription = FString("In Dist To Target Key: " + InDistToTargetKey.SelectedKeyName.ToString());

	FString FinalMsg = FString::Printf(TEXT("%s\r\nBT_Decorator_%s\r\n\r\n%s\r\n%s"), *FlowAbortDesc, *UBehaviorTreeTypes::GetShortTypeName(this), *FirstDescription, *SecondDescription);

	return FinalMsg;
}

bool UBTDecorator_ShouldAbortAllLogics::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UObject* TargetActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(InTargetActorKey.SelectedKeyName);
	AActor* TargetActor = Cast<AActor>(TargetActorObject);
	float DistToTarget = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(InDistToTargetKey.SelectedKeyName);

	bool bIsTargetActorDead = false;
	bool bIsOwningPawnDead = false;

	if (TargetActor)
	{
		if (UMoonveilFunctionLibrary::NativeDoesActorHaveGameplayTag(TargetActor, FMoonveilGameplayTags::Event_Status_Death))
		{
			bIsTargetActorDead = true;
		}
	}

	AActor* OwningPawn = OwnerComp.GetAIOwner()->GetOwner();
	if (OwningPawn)
	{
		if (UMoonveilFunctionLibrary::NativeDoesActorHaveGameplayTag(OwningPawn, FMoonveilGameplayTags::Event_Status_Death))
		{
			bIsOwningPawnDead = true;
		}
	}

	return bIsTargetActorDead || bIsOwningPawnDead || UKismetMathLibrary::NearlyEqual_FloatFloat(DistToTarget, 0.0f);
}
