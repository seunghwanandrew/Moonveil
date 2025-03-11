// Genesis : The World Creation
#include "AI/BT/Decorators/BTDecorator_ComputeSuccessChance.h"
#include "Kismet/KismetMathLibrary.h"

UBTDecorator_ComputeSuccessChance::UBTDecorator_ComputeSuccessChance()
{
	NodeName = "Calculate Attack Chance";

	INIT_DECORATOR_NODE_NOTIFY_FLAGS();

	SuccesMinValue = 0.5f;
	SuccesMaxValue = 0.5f;
}

FString UBTDecorator_ComputeSuccessChance::GetStaticDescription() const
{
	FString FlowAbortDesc;
	if (FlowAbortMode != EBTFlowAbortMode::None)
	{
		FlowAbortDesc = FString::Printf(TEXT("( aborts %s )"), *UBehaviorTreeTypes::DescribeFlowAbortMode(FlowAbortMode).ToLower());
	}

	const FString FirstKeyDescription = FString::Printf(TEXT("Succes Min Value: %.2f"), SuccesMinValue);
	const FString SecondKeyDescription = FString::Printf(TEXT("Succes Max Value: %.2f"), SuccesMaxValue);

	const FString FinalMsg = FString::Printf(TEXT("%s\r\nBT_Decorator_%s:\r\n\r\n%s\r\n%s"), *FlowAbortDesc, *UBehaviorTreeTypes::GetShortTypeName(this), *FirstKeyDescription, *SecondKeyDescription);

	return FinalMsg;
}

bool UBTDecorator_ComputeSuccessChance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	float Weight = FMath::RandRange(SuccesMinValue, SuccesMaxValue);

	return UKismetMathLibrary::RandomBoolWithWeight(Weight);
}
