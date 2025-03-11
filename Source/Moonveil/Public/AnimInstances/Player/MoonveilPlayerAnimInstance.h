// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/MoonveilCharacterAnimInstance.h"
#include "MoonveilPlayerAnimInstance.generated.h"

class AMoonveilPlayerCharacter;

UCLASS()
class MOONVEIL_API UMoonveilPlayerAnimInstance : public UMoonveilCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|References")
	AMoonveilPlayerCharacter* PlayerRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|GroundLocomotion")
	float ThresholdTimerToEnterRelaxState = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|GroundLocomotion")
	bool bShouldEnterRelaxState = false;

	float IdleStateTimeDuration = 0.0f;
};
