// Genesis : The World Creation
#include "AI/BT/Services/BTService_OrientDirectToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"

void UBTService_OrientDirectToTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BlackboardAsset = GetBlackboardAsset();
	if (BlackboardAsset)
	{
		InTargetActorKey.ResolveSelectedKey(*BlackboardAsset);
	}
}

FString UBTService_OrientDirectToTarget::GetStaticDescription() const
{
	Super::GetStaticDescription();

	const FString FirstKeyDescription = InTargetActorKey.SelectedKeyName.ToString();

	const FString FinalMsg = FString::Printf(TEXT("%s: %s \r\n\r\nTargetActor: %s"), *UBehaviorTreeTypes::GetShortTypeName(this), *GetStaticServiceDescription(), *FirstKeyDescription);

	return FinalMsg;
}

UBTService_OrientDirectToTarget::UBTService_OrientDirectToTarget()
{
	NodeName = TEXT("BTService_Orient Direction To Target");

	INIT_SERVICE_NODE_NOTIFY_FLAGS();

	RotationInterSpeed = 6.0f;
	Interval = 0.0f;
	RandomDeviation = 0.0f;

	InTargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, InTargetActorKey), AActor::StaticClass());
}

void UBTService_OrientDirectToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UObject* TargetActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("TargetActor")));
	AActor* TargetActor = TargetActorObject ? Cast<AActor>(TargetActorObject) : nullptr;

	APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (TargetActor && OwningPawn)
	{
		const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(OwningPawn->GetActorLocation(), TargetActor->GetActorLocation());
		const FRotator TargetRotation = FMath::RInterpTo(OwningPawn->GetActorRotation(), LookAtRotation, DeltaSeconds, RotationInterSpeed);

		OwningPawn->SetActorRotation(TargetRotation);
	}
}
