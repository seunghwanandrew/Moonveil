// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "Moonveil_GE_ExecCalcDamageHandle.generated.h"

UCLASS()
class MOONVEIL_API UMoonveil_GE_ExecCalcDamageHandle : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UMoonveil_GE_ExecCalcDamageHandle();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

protected:
};
