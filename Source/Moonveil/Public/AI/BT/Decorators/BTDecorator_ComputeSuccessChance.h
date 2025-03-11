// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_ComputeSuccessChance.generated.h"


UCLASS()
class MOONVEIL_API UBTDecorator_ComputeSuccessChance : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_ComputeSuccessChance();
	virtual FString GetStaticDescription() const;
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "1.0"))
	float SuccesMinValue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "1.0"))
	float SuccesMaxValue;

};
