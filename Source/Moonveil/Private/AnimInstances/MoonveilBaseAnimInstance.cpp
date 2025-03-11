// Genesis : The World Creation
#include "AnimInstances/MoonveilBaseAnimInstance.h"
#include "FunctionLibrary/MoonveilFunctionLibrary.h"

bool UMoonveilBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
    APawn* PawnRef = TryGetPawnOwner();

    if (PawnRef)
    {
        return UMoonveilFunctionLibrary::NativeDoesActorHaveGameplayTag(PawnRef, TagToCheck);
    }

    return false;
}
