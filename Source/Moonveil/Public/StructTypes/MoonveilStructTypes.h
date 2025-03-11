// Genesis : The World Creation
#pragma once

#include "GameplayTagContainer.h"
#include "AbilitySystem/Abilities/MoonveilPlayerGameplayAbility.h"
#include "ScalableFloat.h"
#include "MoonveilStructTypes.generated.h"

class UMoonveilPlayerAnimLayer;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FPlayerGameplayAbilitySet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "AbilityInputTag"))
	FGameplayTag AbilityInputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UMoonveilPlayerGameplayAbility> PlayerAbility;

	bool IsValid() const;
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData|InputMappingContext")
	UInputMappingContext* WeaponInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData|AnimLayer")
	TSubclassOf<UMoonveilPlayerAnimLayer> AnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData|Ability", meta = (TitleProperty = "AbilityInputTag"))
	TArray<FPlayerGameplayAbilitySet> WeaponAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData|WeaponStats")
	FScalableFloat WeaponBaseDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData|WeaponIcon")
	TSoftObjectPtr<UTexture2D> WeaponIcon;
};
