// Genesis : The World Creation
#include "AbilitySystem/Abilities/MoonveilPlayerGameplayAbility.h"
#include "Characters/MoonveilPlayerCharacter.h"
#include "Controllers/MoonveilPlayerController.h"
#include "AbilitySystemComponent.h"
#include "GamePlayTags/MoonveilGameplayTags.h"

AMoonveilPlayerCharacter* UMoonveilPlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
	if (!PlayerRef.IsValid())
	{
		PlayerRef = Cast<AMoonveilPlayerCharacter>(CurrentActorInfo->AvatarActor);
	}
	return PlayerRef.IsValid() ? PlayerRef.Get() : nullptr;
}

AMoonveilPlayerController* UMoonveilPlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if (!PlayerControllerRef.IsValid())
	{
		PlayerControllerRef = Cast<AMoonveilPlayerController>(CurrentActorInfo->PlayerController);
	}
	return PlayerControllerRef.IsValid() ? PlayerControllerRef.Get() : nullptr;
}

UMoonveilPlayerCombatComponent* UMoonveilPlayerGameplayAbility::GetPlayerCombatComponentFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerCombatComponent();
}

UMoonveilAbilitySystemComponent* UMoonveilPlayerGameplayAbility::GetPlayerAbilitySystemComponentFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetCharacterAbilitySystemComponent();
}

FGameplayEffectSpecHandle UMoonveilPlayerGameplayAbility::MakeGameplayEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float WeaponBaseDamage, FGameplayTag CurrentAttackType, int32 ComboCount)
{
	AActor* SourceActor = GetAvatarActorFromActorInfo();

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(SourceActor);
	ContextHandle.AddInstigator(SourceActor, SourceActor);

	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), ContextHandle);

	SpecHandle.Data->SetSetByCallerMagnitude(FMoonveilGameplayTags::Shared_SetByCaller_BaseDamage, WeaponBaseDamage);

	if (CurrentAttackType.IsValid())
	{
		SpecHandle.Data->SetSetByCallerMagnitude(CurrentAttackType, ComboCount);
	}

	return SpecHandle;
}
