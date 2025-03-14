	// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MoonveilBasicGameplayAbility.h"
#include "MoonveilEnemyGameplayAbility.generated.h"

class AMoonveilEnemyCharacter;
class UMoonveilEnemyCombatComponent;

UCLASS()
class MOONVEIL_API UMoonveilEnemyGameplayAbility : public UMoonveilBasicGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Moonveil|GetReferences")
	AMoonveilEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Moonveil|GetReferences")
	UMoonveilEnemyCombatComponent* GetPlayerCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Moonveil|Ability")
	FGameplayEffectSpecHandle MakeGameplayEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScaleFloat);

private:
	TWeakObjectPtr<AMoonveilEnemyCharacter> EnemyRef;
};
