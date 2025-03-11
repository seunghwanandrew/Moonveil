// Genesis : The World Creation
#include "AbilitySystem/Abilities/MoonveilBasicGameplayAbility.h"
#include "AbilitySystem/MoonveilAbilitySystemComponent.h"
#include "Components/Combat/MoonveilBaseCombatComponent.h"
#include "FunctionLibrary/MoonveilFunctionLibrary.h"

void UMoonveilBasicGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == FMoonveilAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	};
}

void UMoonveilBasicGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == FMoonveilAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UMoonveilBaseCombatComponent* UMoonveilBasicGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UMoonveilBaseCombatComponent>();
}

FActiveGameplayEffectHandle UMoonveilBasicGameplayAbility::NativeApplyGameplayEffectHandleToTargetActor(AActor* TargetActor, const FGameplayEffectSpecHandle& SpecHandle)
{
	UAbilitySystemComponent* TargetASC = UMoonveilFunctionLibrary::NativeGetAbilitySystemComponentFromActor(TargetActor);

	return TargetASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data, TargetASC);
}

FActiveGameplayEffectHandle UMoonveilBasicGameplayAbility::BP_ApplyGameplayEffectHandleToTargetActor(AActor* TargetActor, const FGameplayEffectSpecHandle& SpecHandle, ESuccessType& SuccessType)
{
	FActiveGameplayEffectHandle EffectHandle = NativeApplyGameplayEffectHandleToTargetActor(TargetActor, SpecHandle);

	SuccessType = EffectHandle.WasSuccessfullyApplied() ? ESuccessType::Success : ESuccessType::Fail;

	return EffectHandle;
}
