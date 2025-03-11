// Genesis : The World Creation
#include "AI/BT/Services/BTService_UpdateMotionWarpTarget.h"
#include "AIController.h"
#include "Characters/MoonveilEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MotionWarpingComponent.h"
#include "MoonveilDebugHelpers.h"


UBTService_UpdateMotionWarpTarget::UBTService_UpdateMotionWarpTarget()
{
	NodeName = "Update Motion Warping Target Actor";

	InTargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, InTargetActorKey), AActor::StaticClass());
}

void UBTService_UpdateMotionWarpTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BlackboardAsset = GetBlackboardAsset();

	if (!BlackboardAsset) return;
	InTargetActorKey.ResolveSelectedKey(*BlackboardAsset);
}

FString UBTService_UpdateMotionWarpTarget::GetStaticDescription() const
{
	Super::GetStaticDescription();

	const FString FirstKeyDescription = FString("In Target Actor Key: " + InTargetActorKey.SelectedKeyName.ToString());

	return FString::Printf(TEXT("BT_Service_%s: %s\r\n%s"), *UBehaviorTreeTypes::GetShortTypeName(this), *GetStaticServiceDescription(), *FirstKeyDescription);
}

void UBTService_UpdateMotionWarpTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	EnemyRef = Cast<AMoonveilEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (EnemyRef)
	{
		UObject* TargetActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");
		AActor* TargetActor = Cast<AActor>(TargetActorObject);
		if (TargetActor)
		{
			FVector ActorLocation = TargetActor->GetActorLocation();
			UMotionWarpingComponent* MotionWarpingComponent = EnemyRef->GetMotionWarpingComponent();
			MotionWarpingComponent->AddOrUpdateWarpTargetFromLocation(FName(TEXT("WarpTarget")), ActorLocation);
		}
	}
}
