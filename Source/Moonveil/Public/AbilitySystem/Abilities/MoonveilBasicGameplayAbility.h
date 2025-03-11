// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "EnumTypes/MoonveilEnumTypes.h"
#include "MoonveilBasicGameplayAbility.generated.h"

class UMoonveilBaseCombatComponent;

UCLASS()
class MOONVEIL_API UMoonveilBasicGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintCallable, Category = "CallFunction|Combat")
	UMoonveilBaseCombatComponent* GetPawnCombatComponentFromActorInfo() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilitySystem|Policy")
	FMoonveilAbilityActivationPolicy AbilityActivationPolicy = FMoonveilAbilityActivationPolicy::OnTriggered;

	FActiveGameplayEffectHandle NativeApplyGameplayEffectHandleToTargetActor(AActor* TargetActor, const FGameplayEffectSpecHandle& SpecHandle);

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|AbilityEffect", meta = (DisplayName = "Apply Gameplay Effect Handle To Target Actor", ExpandEnumAsExecs = "SuccessType"))
	FActiveGameplayEffectHandle BP_ApplyGameplayEffectHandleToTargetActor(AActor* TargetActor, const FGameplayEffectSpecHandle& SpecHandle, ESuccessType& SuccessType);
};
