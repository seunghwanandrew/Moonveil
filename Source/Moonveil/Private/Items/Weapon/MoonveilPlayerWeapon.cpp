// Genesis : The World Creation
#include "Items/Weapon/MoonveilPlayerWeapon.h"

void AMoonveilPlayerWeapon::AssignActivatedAbilitySpecHandle(const TArray<FGameplayAbilitySpecHandle>& InSpecHandle)
{
	ActivatedAbilitySpecHandle = InSpecHandle;
}

TArray<FGameplayAbilitySpecHandle> AMoonveilPlayerWeapon::GetActivatedAbilitySpecHandle()
{
	if (ActivatedAbilitySpecHandle.IsEmpty()) return TArray<FGameplayAbilitySpecHandle>();
	return ActivatedAbilitySpecHandle;
}
