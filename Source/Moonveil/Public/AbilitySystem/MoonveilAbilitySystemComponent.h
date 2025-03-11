// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MoonveilAbilitySystemComponent.generated.h"

struct FPlayerGameplayAbilitySet;

UCLASS()
class MOONVEIL_API UMoonveilAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Moonveil|Ability", meta = (ApplyLevel = "1"))
	void GrantWeaponAbility(const TArray<FPlayerGameplayAbilitySet>& WeaponAbility, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutSpecHandle);
	UFUNCTION(BlueprintCallable, Category = "Moonveil|Ability")
	void RemoveWeaponAbility(TArray<FGameplayAbilitySpecHandle> SpecHandle);
	UFUNCTION(BlueprintCallable, Category = "Moonveil|Ability")
	bool TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate);

	void TagAbilityOnPressed(FGameplayTag AbilityInputTag);
	void TagAbilityOnReleased(FGameplayTag AbilityInputTag);
};
