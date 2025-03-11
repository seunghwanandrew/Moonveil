// Genesis : The World Creation

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/MoonveilBaseCombatComponent.h"
#include "MoonveilPlayerCombatComponent.generated.h"

class AMoonveilPlayerWeapon;

UCLASS()
class MOONVEIL_API UMoonveilPlayerCombatComponent : public UMoonveilBaseCombatComponent
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, Category = "Combat|Weapon")
	AMoonveilPlayerWeapon* FindPlayerCarriedWeaponByTag(FGameplayTag WeaponTagToFind) const;

	UFUNCTION(BlueprintCallable, Category = "Combat|Weapon")
	AMoonveilPlayerWeapon* GetPlayerCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Combat|Weapon")
	float GetPlayerCurrentEquippedWeaponDamageAtLevel(float Level) const;

	virtual void TargetOnWeapon(AActor* Target) override;
	virtual void TargetOffWeapon(AActor* Target) override;
};
