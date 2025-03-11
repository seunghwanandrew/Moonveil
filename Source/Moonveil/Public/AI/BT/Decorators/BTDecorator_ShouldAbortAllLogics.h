// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_ShouldAbortAllLogics.generated.h"

UCLASS()
class MOONVEIL_API UBTDecorator_ShouldAbortAllLogics : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_ShouldAbortAllLogics();
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticDescription() const override;
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
	UPROPERTY(VisibleAnywhere)
	FBlackboardKeySelector InTargetActorKey;
	UPROPERTY(VisibleAnywhere)
	FBlackboardKeySelector InDistToTargetKey;
};
