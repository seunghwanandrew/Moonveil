// Genesis : The World Creation
#include "AnimInstances/Player/MoonveilPlayerAnimInstance.h"
#include "Characters/MoonveilPlayerCharacter.h"

void UMoonveilPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (CharacterRef)
	{
		PlayerRef = Cast<AMoonveilPlayerCharacter>(CharacterRef);
	}
}

void UMoonveilPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	if (bHasAcceleration)
	{
		IdleStateTimeDuration = 0.0f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleStateTimeDuration += DeltaSeconds;
		bShouldEnterRelaxState = IdleStateTimeDuration > ThresholdTimerToEnterRelaxState;
	}
}
