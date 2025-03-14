// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "EnumTypes/MoonveilEnumTypes.h"
#include "Components/Combat/MoonveilBaseCombatComponent.h"
#include "MoonveilFunctionLibrary.generated.h"

class UMoonveilAbilitySystemComponent;
struct FScalableFloat;

UCLASS()
class MOONVEIL_API UMoonveilFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static UMoonveilAbilitySystemComponent*NativeGetAbilitySystemComponentFromActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "MoonveilFunctionLibrary", meta = (DisplayName = "Get Ability System Component From Actor"))
	UMoonveilAbilitySystemComponent* BP_GetAbilitySystemComponentFromActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "MoonveilFunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* Actor, FGameplayTag TagToAdd);
	
	UFUNCTION(BlueprintCallable, Category = "MoonveilFunctionLibrary")
	static void RemoveGameplayTagFromActorIfHas(AActor* Actor, FGameplayTag TagToRemove);
	
	static bool NativeDoesActorHaveGameplayTag(AActor* Actor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "MoonveilFunctionLibrary", meta = (DisplayName = "Does Actor Have Gameplay Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveGameplayTag(AActor* Actor, FGameplayTag TagToCheck, EConfirmType& OutConfirmType);

	static UMoonveilBaseCombatComponent* NativeGetPawnCombatComponent(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "MoonveilFunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component", ExpandEnumAsExecs = "OutValidType"))
	static UMoonveilBaseCombatComponent* BP_GetPawnCombatComponent(AActor* Actor, EValidType& OutValidType);

	UFUNCTION(BlueprintCallable, Category = "MoonveilFunctionLibrary")
	static bool IsTargetPawnHostile(APawn* Query, APawn* Target);

	UFUNCTION(BlueprintPure, Category = "MoonveilFunctionLibrary", meta = (ApplyLevel = "1"))
	static float GetFloatValueFromScalableFloatAtLevel(const FScalableFloat& ScalableFloat, int32 ApplyLevel);

	UFUNCTION(BlueprintPure, Category = "MoonveilFunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* Attacker, AActor* Target, float& OutDifferences);

	UFUNCTION(BlueprintPure, Category = "MoonveilFunctionLibrary")
	static bool IsValidBlock(AActor* Attacker, AActor* Target);
};
