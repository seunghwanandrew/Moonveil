// Genesis : The World Creation
#include "AbilitySystem/Abilities/MoonveilEnemyGameplayAbility.h"
#include "Characters/MoonveilEnemyCharacter.h"
#include "AbilitySystem/MoonveilAbilitySystemComponent.h"
#include "GamePlayTags/MoonveilGameplayTags.h"

AMoonveilEnemyCharacter* UMoonveilEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
    if (!EnemyRef.IsValid())
    {
        EnemyRef = Cast<AMoonveilEnemyCharacter>(CurrentActorInfo->AvatarActor);
    }

    return EnemyRef.IsValid() ? EnemyRef.Get() : nullptr;
}

UMoonveilEnemyCombatComponent* UMoonveilEnemyGameplayAbility::GetPlayerCombatComponentFromActorInfo()
{
    if (!GetEnemyCharacterFromActorInfo()) return nullptr;
    return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UMoonveilEnemyGameplayAbility::MakeGameplayEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScaleFloat)
{
    AActor* SourceActor = GetAvatarActorFromActorInfo();

    FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
    ContextHandle.SetAbility(this);
    ContextHandle.AddSourceObject(SourceActor);
    ContextHandle.AddInstigator(SourceActor, SourceActor);

    FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), ContextHandle);

    SpecHandle.Data->SetSetByCallerMagnitude(FMoonveilGameplayTags::Shared_SetByCaller_BaseDamage, InDamageScaleFloat.GetValueAtLevel(GetAbilityLevel()));

    return SpecHandle;
}
