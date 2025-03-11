// Genesis : The World Creation

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/MoonveilBaseAnimInstance.h"
#include "MoonveilCharacterAnimInstance.generated.h"

class AMoonveilBaseCharacter;
class UCharacterMovementComponent;

UCLASS()
class MOONVEIL_API UMoonveilCharacterAnimInstance : public UMoonveilBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|References")
	AMoonveilBaseCharacter* CharacterRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|References")
	UCharacterMovementComponent* MovementComponentRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|GroundLocomotion")
	float GroundSpeed = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|GroundLocomotion")
	bool bHasAcceleration = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|GroundLocomotion")
	float LocomotionDirection = 0.0f;

};
