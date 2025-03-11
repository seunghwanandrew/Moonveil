// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MoonveilBasicGameplayAbility.h"
#include "GameplayTagContainer.h"
#include "MoonveilPlayerGameplayAbility.generated.h"

class AMoonveilPlayerCharacter;
class AMoonveilPlayerController;
class UMoonveilPlayerCombatComponent;
class UMoonveilAbilitySystemComponent;
class UGameplayEffect;

UCLASS()
class MOONVEIL_API UMoonveilPlayerGameplayAbility : public UMoonveilBasicGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Moonveil|GetReferences")
	AMoonveilPlayerCharacter* GetPlayerCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Moonveil|GetReferences")
	AMoonveilPlayerController* GetPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Moonveil|GetReferences")
	UMoonveilPlayerCombatComponent* GetPlayerCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Moonveil|Ability")
	UMoonveilAbilitySystemComponent* GetPlayerAbilitySystemComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Moonveil|Ability")
	FGameplayEffectSpecHandle MakeGameplayEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float WeaponBaseDamage, FGameplayTag CurrentAttackType, int32 ComboCount);

private:
	TWeakObjectPtr<AMoonveilPlayerCharacter> PlayerRef;
	TWeakObjectPtr<AMoonveilPlayerController> PlayerControllerRef;
	TWeakObjectPtr<UMoonveilPlayerCombatComponent> PlayerCombatComponentRef;
};
