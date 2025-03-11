// Genesis : The World Creation
#include "AnimInstances/MoonveilCharacterAnimInstance.h"
#include "Characters/MoonveilBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

void UMoonveilCharacterAnimInstance::NativeInitializeAnimation()
{
	CharacterRef = Cast<AMoonveilBaseCharacter>(TryGetPawnOwner());
	if (CharacterRef)
	{
		MovementComponentRef = CharacterRef->GetCharacterMovement();
	}
}

void UMoonveilCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (MovementComponentRef)
	{
		GroundSpeed = MovementComponentRef->Velocity.Size2D();
		bHasAcceleration = MovementComponentRef->GetCurrentAcceleration().SizeSquared2D() > 0.0f;
		LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(MovementComponentRef->Velocity, CharacterRef->GetActorRotation());
	}
}
