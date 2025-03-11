// Genesis : The World Creation
#include "DataAssets/StartUp/MoonveilPlayerStartUpDataAsset.h"
#include "AbilitySystem/Abilities/MoonveilPlayerGameplayAbility.h"
#include "AbilitySystem/MoonveilAbilitySystemComponent.h"

void UMoonveilPlayerStartUpDataAsset::GiveAbilityToAbilitySystemComponent(UMoonveilAbilitySystemComponent* AbilitySystemComponentToGive, int32 ApplyLevel)
{
	Super::GiveAbilityToAbilitySystemComponent(AbilitySystemComponentToGive, ApplyLevel);

	for (const FPlayerGameplayAbilitySet& Ability : PlayerAbilitySet) 
	{
		if (!Ability.IsValid()) continue;

		FGameplayAbilitySpec Spec(Ability.PlayerAbility);
		Spec.SourceObject = AbilitySystemComponentToGive->GetAvatarActor();
		Spec.Level = ApplyLevel;
		Spec.DynamicAbilityTags.AddTag(Ability.AbilityInputTag);

		AbilitySystemComponentToGive->GiveAbility(Spec);
	}
}
