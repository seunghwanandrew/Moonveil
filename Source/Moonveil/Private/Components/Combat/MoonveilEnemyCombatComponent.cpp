// Genesis : The World Creation
#include "Components/Combat/MoonveilEnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GamePlayTags/MoonveilGameplayTags.h"
#include "FunctionLibrary/MoonveilFunctionLibrary.h"

#include "MoonveilDebugHelpers.h"

void UMoonveilEnemyCombatComponent::TargetOnWeapon(AActor* Target)
{
	Super::TargetOnWeapon(Target);

	if (OverlappedTargetArray.Contains(Target)) return;

	OverlappedTargetArray.AddUnique(Target);

	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = UMoonveilFunctionLibrary::NativeDoesActorHaveGameplayTag(Target, FMoonveilGameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable = false;

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		bIsValidBlock = UMoonveilFunctionLibrary::IsValidBlock(GetOwningPawn(), Target);
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = Target;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Target, FMoonveilGameplayTags::Event_Block_Successed, EventData);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), FMoonveilGameplayTags::Event_Attack_Melee, EventData);
	}
}

void UMoonveilEnemyCombatComponent::TargetOffWeapon(AActor* Target)
{
	Super::TargetOffWeapon(Target);
}
