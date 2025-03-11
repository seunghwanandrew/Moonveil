// Genesis : The World Creation
#include "AnimInstances/Player/MoonveilPlayerAnimLayer.h"
#include "AnimInstances/MoonveilCharacterAnimInstance.h"

UMoonveilCharacterAnimInstance* UMoonveilPlayerAnimLayer::GetPlayerAnimInstance() const
{
	return Cast<UMoonveilCharacterAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
