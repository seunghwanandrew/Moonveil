// Genesis : The World Creation
#include "DataAssets/StartUp/MoonveilBaseStartUpDataAsset.h"
#include "AbilitySystem/MoonveilAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/MoonveilBasicGameplayAbility.h"


void UMoonveilBaseStartUpDataAsset::GiveAbilityToAbilitySystemComponent(UMoonveilAbilitySystemComponent* AbilitySystemComponentToGive, int32 ApplyLevel)
{
	if (!AbilitySystemComponentToGive) return;

	GrantAbilities(OnGivenAbilitySet, AbilitySystemComponentToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilitySet, AbilitySystemComponentToGive, ApplyLevel);

	if (!GameplayEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& Effect : GameplayEffects)
		{
			if (!Effect) continue;

			UGameplayEffect* EffectCDO = Effect->GetDefaultObject<UGameplayEffect>();
			AbilitySystemComponentToGive->ApplyGameplayEffectToSelf(EffectCDO, ApplyLevel, AbilitySystemComponentToGive->MakeEffectContext());
		}
	}
}

void UMoonveilBaseStartUpDataAsset::GrantAbilities(const TArray<TSubclassOf<UMoonveilBasicGameplayAbility>>& AbilityToGrant, UMoonveilAbilitySystemComponent* AbilitySystemComponentToGive, int32 ApplyLevel)
{
	if (AbilityToGrant.IsEmpty()) return;

	for (const TSubclassOf<UMoonveilBasicGameplayAbility>& Ability : AbilityToGrant)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec Spec(Ability);
		Spec.SourceObject = AbilitySystemComponentToGive->GetAvatarActor();
		Spec.Level = ApplyLevel;

		AbilitySystemComponentToGive->GiveAbility(Spec);
	}
}
