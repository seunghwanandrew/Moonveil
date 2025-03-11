// Genesis : The World Creation
#include "DataAssets/StartUp/MoonveilEnemyStartUpDataAsset.h"
#include "AbilitySystem/MoonveilAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/MoonveilEnemyGameplayAbility.h"

#include "MoonveilDebugHelpers.h"

void UMoonveilEnemyStartUpDataAsset::GiveAbilityToAbilitySystemComponent(UMoonveilAbilitySystemComponent* AbilitySystemComponentToGive, int32 ApplyLevel)
{
	Super::GiveAbilityToAbilitySystemComponent(AbilitySystemComponentToGive, ApplyLevel);

	for (const TSubclassOf<UMoonveilEnemyGameplayAbility>& Ability : EnemyAbility)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec Spec(Ability);
		Spec.SourceObject = AbilitySystemComponentToGive->GetAvatarActor();
		Spec.Level = ApplyLevel;
		
		AbilitySystemComponentToGive->GiveAbility(Spec);
	}
}
