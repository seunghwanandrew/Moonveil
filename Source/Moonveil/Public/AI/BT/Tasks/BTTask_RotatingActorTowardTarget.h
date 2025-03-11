// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "AI/BT/Tasks/BTTask_EnemyBase.h"
#include "BTTask_RotatingActorTowardTarget.generated.h"

struct FRotatoingActorTowardTargetTaskMemory
{
	TWeakObjectPtr<APawn> PawnRef;
	TWeakObjectPtr<AActor> TargetActor;

	bool IsValid() const
	{
		return PawnRef.IsValid() && TargetActor.IsValid();
	}
	void Reset()
	{
		PawnRef.Reset();
		TargetActor.Reset();
	}
};

UCLASS()
class MOONVEIL_API UBTTask_RotatingActorTowardTarget : public UBTTask_EnemyBase
{
	GENERATED_BODY()

public:
	UBTTask_RotatingActorTowardTarget();

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual uint16 GetInstanceMemorySize() const override;
	virtual FString GetStaticDescription() const override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	bool HasReachedAnglePrecision(APawn* PawnRef, AActor* TargetActor) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AnglePrecision;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RotationInterpSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBlackboardKeySelector InTargetToFaceKey;
};
