// Genesis : The World Creation
#include "AI/BT/Decorators/BTDecorator_DoesActorHaveTag.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FunctionLibrary/MoonveilFunctionLibrary.h"

UBTDecorator_DoesActorHaveTag::UBTDecorator_DoesActorHaveTag()
{
	NodeName = "Does Actor Have Tag?";

	INIT_DECORATOR_NODE_NOTIFY_FLAGS();

	InActorKeyToCheck.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, InActorKeyToCheck), AActor::StaticClass());
	bInverseConditionCheck = false;
}

void UBTDecorator_DoesActorHaveTag::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		InActorKeyToCheck.ResolveSelectedKey(*BBAsset);
	}
}

FString UBTDecorator_DoesActorHaveTag::GetStaticDescription() const
{
	FString FlowAbortDesc;
	if (FlowAbortMode != EBTFlowAbortMode::None)
	{
		FlowAbortDesc = FString::Printf(TEXT("( aborts %s )"), *UBehaviorTreeTypes::DescribeFlowAbortMode(FlowAbortMode).ToLower());
	}

	FString FirstDescription = FString("In Actor Key To Check:" + InActorKeyToCheck.SelectedKeyName.ToString());
	FString SecondDescription = FString("Gameplay Tag To Check: " + TagToCheck.GetTagName().ToString());
	FString ThirdDescription = bInverseConditionCheck ? FString("Inverse Condition Check: True") : FString("Inverse Condition Check: False");

	FString FinalMsg = FString::Printf(TEXT("%s\r\nBT_Decorator_%s\r\n\r\n%s\r\n%s\r\n%s"), *FlowAbortDesc, *UBehaviorTreeTypes::GetShortTypeName(this), *FirstDescription, *SecondDescription, *ThirdDescription);

	return FinalMsg;
}

bool UBTDecorator_DoesActorHaveTag::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UObject* ActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(InActorKeyToCheck.SelectedKeyName);
	AActor* TargetActor = Cast<AActor>(ActorObject);

	if (TargetActor && TagToCheck.IsValid())
	{
		bool bActorHasTag = UMoonveilFunctionLibrary::NativeDoesActorHaveGameplayTag(TargetActor, TagToCheck);
		if (bActorHasTag)
		{
			if (bInverseConditionCheck) return false;
			else return true; 
		}
		else
		{
			if (bInverseConditionCheck) return true;
			else return false;
		}
	}

	return false;
}
