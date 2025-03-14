// Genesis : The World Creation
#include "Components/Combat/MoonveilPlayerCombatComponent.h"
#include "Items/Weapon/MoonveilPlayerWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GamePlayTags/MoonveilGameplayTags.h"

AMoonveilPlayerWeapon* UMoonveilPlayerCombatComponent::FindPlayerCarriedWeaponByTag(FGameplayTag WeaponTagToFind) const
{
    return Cast<AMoonveilPlayerWeapon>(FindCharacterCarriedWeaponByTag(WeaponTagToFind));
}

AMoonveilPlayerWeapon* UMoonveilPlayerCombatComponent::GetPlayerCurrentEquippedWeapon() const
{
    return Cast<AMoonveilPlayerWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UMoonveilPlayerCombatComponent::GetPlayerCurrentEquippedWeaponDamageAtLevel(float Level) const
{
    return GetPlayerCurrentEquippedWeapon() ? GetPlayerCurrentEquippedWeapon()->GetWeaponData().WeaponBaseDamage.GetValueAtLevel(Level) : 0.0f;
}

void UMoonveilPlayerCombatComponent::TargetOnWeapon(AActor* Target)
{
    Super::TargetOnWeapon(Target);
    if (OverlappedTargetArray.Contains(Target)) return;
    OverlappedTargetArray.AddUnique(Target);

    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = Target;

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), FMoonveilGameplayTags::Event_Attack_Melee, Data);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), FMoonveilGameplayTags::Event_Hit_Pause, FGameplayEventData());
}

void UMoonveilPlayerCombatComponent::TargetOffWeapon(AActor* Target)
{
    Super::TargetOffWeapon(Target);

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), FMoonveilGameplayTags::Event_Hit_Pause, FGameplayEventData());
}
