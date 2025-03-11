// Genesis : The World Creation
#include "StructTypes/MoonveilStructTypes.h"

bool FPlayerGameplayAbilitySet::IsValid() const
{
    return AbilityInputTag.IsValid() && PlayerAbility;
}
