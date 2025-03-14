// Genesis : The World Creation
#include "AbilitySystem/MoonveilAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/MoonveilPlayerGameplayAbility.h"
#include "StructTypes/MoonveilStructTypes.h"
#include "GamePlayTags/MoonveilGameplayTags.h"

void UMoonveilAbilitySystemComponent::GrantWeaponAbility(const TArray<FPlayerGameplayAbilitySet>& WeaponAbility, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutSpecHandle)
{
	for (const FPlayerGameplayAbilitySet& Ability : WeaponAbility)
	{
		if (!Ability.IsValid()) continue;

		FGameplayAbilitySpec Spec(Ability.PlayerAbility);
		Spec.SourceObject = GetAvatarActor();
		Spec.Level = ApplyLevel;
		Spec.DynamicAbilityTags.AddTag(Ability.AbilityInputTag);

		FGameplayAbilitySpecHandle SpecHandle = GiveAbility(Spec);

		OutSpecHandle.AddUnique(SpecHandle);
	}
}

void UMoonveilAbilitySystemComponent::RemoveWeaponAbility(TArray<FGameplayAbilitySpecHandle> SpecHandle)
{
	if (SpecHandle.IsEmpty()) return;

	for (const FGameplayAbilitySpecHandle& Handle : SpecHandle)
	{
		if (!Handle.IsValid()) continue;

		ClearAbility(Handle);
	}

	SpecHandle.Empty();
}

bool UMoonveilAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{
	if (!AbilityTagToActivate.IsValid()) return false;

	TArray<FGameplayAbilitySpec*> FoundAbilitySpecByTag;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(), FoundAbilitySpecByTag);

	if (!FoundAbilitySpecByTag.IsEmpty())
	{
		const int32 RandomIndex = FMath::RandRange(0, FoundAbilitySpecByTag.Num() - 1);
		FGameplayAbilitySpec* SpecToActivate = FoundAbilitySpecByTag[RandomIndex];

		check(SpecToActivate);

		if (!SpecToActivate->IsActive())
		{
			return TryActivateAbility(SpecToActivate->Handle);
		}
	}

	return false;
}

void UMoonveilAbilitySystemComponent::TagAbilityOnPressed(FGameplayTag AbilityInputTag)
{
	for (const FGameplayAbilitySpec& Ability : GetActivatableAbilities())
	{
		if (!Ability.DynamicAbilityTags.HasTagExact(AbilityInputTag)) continue;

		if (AbilityInputTag.MatchesTag(FMoonveilGameplayTags::InputTag_Toggleable))
		{
			if (Ability.IsActive())
			{
				CancelAbilityHandle(Ability.Handle);
			}
			else
			{
				TryActivateAbility(Ability.Handle);
			}
		}
		else
		{
			TryActivateAbility(Ability.Handle);
		}
	}
}

void UMoonveilAbilitySystemComponent::TagAbilityOnReleased(FGameplayTag AbilityInputTag)
{
	if (!AbilityInputTag.IsValid() || !AbilityInputTag.MatchesTag(FMoonveilGameplayTags::InputTag_OnPressed)) return;

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(AbilityInputTag) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
	}
}
