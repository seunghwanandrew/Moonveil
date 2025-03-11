// Genesis : The World Creation
#include "Components/Combat/MoonveilBaseCombatComponent.h"
#include "Items/Weapon/MoonveilBaseWeapon.h"
#include "Components/BoxComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GamePlayTags/MoonveilGameplayTags.h"

void UMoonveilBaseCombatComponent::RegisterSpawnedWeapon(AMoonveilBaseWeapon* WeaponToRegister, const FGameplayTag& WeaponTagToRegister, bool bShouldbeEquippedAsCurrentWeapon)
{
    if (CharacterCarriedWeapons.Contains(WeaponTagToRegister)) return;

    WeaponToRegister->WeaponTargetOn.BindUObject(this, &UMoonveilBaseCombatComponent::TargetOnWeapon);
    WeaponToRegister->WeaponTargetOff.BindUObject(this, &UMoonveilBaseCombatComponent::TargetOffWeapon);

    CharacterCarriedWeapons.Emplace(WeaponTagToRegister, WeaponToRegister);

    if (bShouldbeEquippedAsCurrentWeapon)
    {
        CurrentEquippedWeaponTag = WeaponTagToRegister;
    }
}

AMoonveilBaseWeapon* UMoonveilBaseCombatComponent::FindCharacterCarriedWeaponByTag(FGameplayTag WeaponTagToFind) const
{
    if (!CharacterCarriedWeapons.Contains(WeaponTagToFind)) return nullptr;

    AMoonveilBaseWeapon* const* FoundWeapon = CharacterCarriedWeapons.Find(WeaponTagToFind);

    return *FoundWeapon;
}

AMoonveilBaseWeapon* UMoonveilBaseCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
    return FindCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UMoonveilBaseCombatComponent::ToggleWeaponCollision(bool bWeaponCollisionEnable, EDamageType DamageType)
{
    switch (DamageType)
    {
    case EDamageType::CurrentEquippedWeapon:
    {
        if (!CurrentEquippedWeaponTag.IsValid()) return;
        AMoonveilBaseWeapon* EquippedWeapon = GetCharacterCurrentEquippedWeapon();
        UBoxComponent* WeaponCollisionBox = EquippedWeapon->GetWeaponCollisionBox();
        if (bWeaponCollisionEnable)
        {
            WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        }
        else
        {
            WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            OverlappedTargetArray.Empty();
        }
        break;
    }
    case EDamageType::LeftHand:
        break;
    case EDamageType::RightHand:
        break;
    default:
        break;
    }    
}

void UMoonveilBaseCombatComponent::TargetOnWeapon(AActor* Target)
{
    if (OverlappedTargetArray.Contains(Target)) return;
    OverlappedTargetArray.AddUnique(Target);

    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = Target;

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), FMoonveilGameplayTags::Event_Attack_Melee, Data);
}

void UMoonveilBaseCombatComponent::TargetOffWeapon(AActor* Target)
{
}
