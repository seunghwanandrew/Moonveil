// Genesis : The World Creation
#include "Components/Combat/MoonveilEnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GamePlayTags/MoonveilGameplayTags.h"

void UMoonveilEnemyCombatComponent::TargetOnWeapon(AActor* Target)
{
	Super::TargetOnWeapon(Target);

	if (OverlappedTargetArray.Contains(Target)) return;

	OverlappedTargetArray.AddUnique(Target);

	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = false;
	const bool bIsMyAttackUnblockable = false;

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		// TODO - Check It the Block Is Valid
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = Target;

	if (bIsValidBlock)
	{
		// TODO - Handle Blocking Process
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), FMoonveilGameplayTags::Event_Hit_Melee, EventData);
	}
}

void UMoonveilEnemyCombatComponent::TargetOffWeapon(AActor* Target)
{
	Super::TargetOffWeapon(Target);
}
