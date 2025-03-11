// Genesis : The World Creation
#pragma once

#include "NativeGameplayTags.h"

namespace FMoonveilGameplayTags
{
	// Input Tags //
#pragma region InputTag
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Equip_Sword);
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Unequip_Sword);
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Attack_Light_Sword);
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Attack_Heavy_Sword);
#pragma endregion

	// Player Tags //
#pragma region PlayerTag
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Sword);

	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Sword);
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Sword);
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Sword);
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Sword);
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause);

	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);

	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_Attack_Light);
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_Attack_Heavy);
#pragma endregion

	// Enemy Tags //
#pragma region EnemyTag
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee);
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged);

	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);

	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Strafing);
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_UnderAttack);
#pragma endregion

	// Event Tags //
#pragma region EventTag
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Equip_Sword);
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Unequip_Sword);
		
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Attack_Melee);

	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Hit_Melee);
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Hit_React);
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Hit_Pause);

	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Status_Death);
#pragma endregion

	// Shared Tags //
#pragma region SharedTag
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReaction);
	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death);

	MOONVEIL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage);
#pragma endregion

}