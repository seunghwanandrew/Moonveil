// Genesis : The World Creation
#include "AI/BT/Services/BTService_GetDistanceToActor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"

#include "MoonveilDebugHelpers.h"


UBTService_GetDistanceToActor::UBTService_GetDistanceToActor()
{
	NodeName = TEXT("BTService_Get Dist To Target");

	INIT_SERVICE_NODE_NOTIFY_FLAGS();

	Interval = 0.2;
	RandomDeviation = 0.0f;

	InTargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, InTargetActorKey), AActor::StaticClass());
	OutDistToTargetKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, OutDistToTargetKey));
}

void UBTService_GetDistanceToActor::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BlackboardAsset = GetBlackboardAsset();

	if (!BlackboardAsset) return;
	InTargetActorKey.ResolveSelectedKey(*BlackboardAsset);
	OutDistToTargetKey.ResolveSelectedKey(*BlackboardAsset);
}

FString UBTService_GetDistanceToActor::GetStaticDescription() const
{
	Super::GetStaticDescription();
	const FString FirstKeyDescription = FString("In Target key: " + InTargetActorKey.SelectedKeyName.ToString());
	const FString SecondKeyDescription = FString("Out Dist To TargetKey: " + OutDistToTargetKey.SelectedKeyName.ToString());

	const FString FinalText = FString::Printf(TEXT("BT_Service_%s: %s \r\n\r\n%s\r\n%s"), 
		*UBehaviorTreeTypes::GetShortTypeName(this), *GetStaticServiceDescription(), *FirstKeyDescription, *SecondKeyDescription);

	return FinalText;
}

void UBTService_GetDistanceToActor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	UObject* TargetActorObject = Blackboard->GetValueAsObject(FName(TEXT("TargetActor")));
	AActor* TargetActor = Cast<AActor>(TargetActorObject);

	float DistanceToTarget = OwnerComp.GetOwner<AAIController>()->GetPawn()->GetDistanceTo(TargetActor);

	Blackboard->SetValueAsFloat(FName(TEXT("DistToTarget")), DistanceToTarget);
}
