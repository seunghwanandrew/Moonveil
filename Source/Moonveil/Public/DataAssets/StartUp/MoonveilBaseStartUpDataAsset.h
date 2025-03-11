// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MoonveilBaseStartUpDataAsset.generated.h"

class UMoonveilAbilitySystemComponent;
class UMoonveilBasicGameplayAbility;
class UGameplayEffect;

UCLASS()
class MOONVEIL_API UMoonveilBaseStartUpDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void GiveAbilityToAbilitySystemComponent(UMoonveilAbilitySystemComponent* AbilitySystemComponentToGive, int32 ApplyLevel = 1);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|OnGiven")
	TArray<TSubclassOf<UMoonveilBasicGameplayAbility>> OnGivenAbilitySet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|OnGiven")
	TArray<TSubclassOf<UMoonveilBasicGameplayAbility>> ReactiveAbilitySet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayEffects")
	TArray<TSubclassOf<UGameplayEffect>> GameplayEffects;

	void GrantAbilities(const TArray<TSubclassOf<UMoonveilBasicGameplayAbility>>& AbilityToGrant, UMoonveilAbilitySystemComponent* AbilitySystemComponentToGive, int32 ApplyLevel = 1);

};
