// Genesis : The World Creation
#include "AI/BT/Tasks/BTTask_RotatingActorTowardTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_RotatingActorTowardTarget::UBTTask_RotatingActorTowardTarget()
{
    NodeName = TEXT("Rotating Actor Toward Target");

    INIT_TASK_NODE_NOTIFY_FLAGS();

    AnglePrecision = 10.0f;
    RotationInterpSpeed = 6.0f;

    InTargetToFaceKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, InTargetToFaceKey), AActor::StaticClass());
}

void UBTTask_RotatingActorTowardTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
    if (UBlackboardData* BBAsset = GetBlackboardAsset())
    {
        InTargetToFaceKey.ResolveSelectedKey(*BBAsset);
    }
}

uint16 UBTTask_RotatingActorTowardTarget::GetInstanceMemorySize() const
{
    return sizeof(FRotatoingActorTowardTargetTaskMemory);
}

FString UBTTask_RotatingActorTowardTarget::GetStaticDescription() const
{
    const FString FristDescription = FString("In Target To Face Key: " + InTargetToFaceKey.SelectedKeyName.ToString());
    const FString SecondDescription = FString::Printf(TEXT("Angle Precision: %.1f"), AnglePrecision);
    const FString ThirdDescription = FString::Printf(TEXT("Rotation Interp Speed: %.1f"), RotationInterpSpeed);

    const FString FinalMsg = FString::Printf(TEXT("BT_Task_%s\r\n\r\n%s\r\n%s\r\n%s"), *UBehaviorTreeTypes::GetShortTypeName(this), *FristDescription, *SecondDescription, *ThirdDescription);

    return FinalMsg;
}

EBTNodeResult::Type UBTTask_RotatingActorTowardTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    UObject* TargetObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(InTargetToFaceKey.SelectedKeyName);
    AActor* TargetActor = Cast<AActor>(TargetObject);

    APawn* PawnRef = OwnerComp.GetAIOwner()->GetPawn();

    FRotatoingActorTowardTargetTaskMemory* Memory = CastInstanceNodeMemory<FRotatoingActorTowardTargetTaskMemory>(NodeMemory);

    check(Memory);

    Memory->PawnRef = PawnRef;
    Memory->TargetActor = TargetActor;

    if (!Memory->IsValid())
    {
        return EBTNodeResult::Failed;
    }

    if (HasReachedAnglePrecision(PawnRef, TargetActor))
    {
        Memory->Reset();
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::InProgress;
}

void UBTTask_RotatingActorTowardTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    FRotatoingActorTowardTargetTaskMemory* Memory = CastInstanceNodeMemory<FRotatoingActorTowardTargetTaskMemory>(NodeMemory);

    if (!Memory->IsValid())
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    }

    if (HasReachedAnglePrecision(Memory->PawnRef.Get(), Memory->TargetActor.Get()))
    {
        Memory->Reset();
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
    else
    {
        const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Memory->PawnRef.Get()->GetActorLocation(), Memory->TargetActor->GetActorLocation());
        const FRotator TargetRotation = FMath::RInterpTo(Memory->PawnRef->GetActorRotation(), LookAtRotation, DeltaSeconds, RotationInterpSpeed);

        Memory->PawnRef->SetActorRotation(TargetRotation);
    }
}

bool UBTTask_RotatingActorTowardTarget::HasReachedAnglePrecision(APawn* PawnRef, AActor* TargetActor) const
{
    const FVector QueryForward = PawnRef->GetActorForwardVector();
    const FVector QueryToTargetNormalized = (TargetActor->GetActorLocation() - PawnRef->GetActorLocation()).GetSafeNormal();

    const float DotResult = FVector::DotProduct(QueryForward, QueryToTargetNormalized);
    const float AngleDifferences = UKismetMathLibrary::DegAcos(DotResult);

    return AngleDifferences <= AnglePrecision;
}
