// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_DoesActorHaveTag.generated.h"

UCLASS()
class MOONVEIL_API UBTDecorator_DoesActorHaveTag : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_DoesActorHaveTag();
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticDescription() const override;
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector InActorKeyToCheck;

	UPROPERTY(EditAnywhere)
	FGameplayTag TagToCheck;

	UPROPERTY(EditAnywhere)
	bool bInverseConditionCheck;
};
