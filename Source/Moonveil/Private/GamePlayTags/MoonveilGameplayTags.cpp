// Genesis : The World Creation
#include "GamePlayTags/MoonveilGameplayTags.h"

namespace FMoonveilGameplayTags
{
	// Input Tags //
#pragma region InputTag
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip_Sword, "InputTag.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Unequip_Sword, "InputTag.Unequip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Light_Sword, "InputTag.Attack.Light.Sword");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Heavy_Sword, "InputTag.Attack.Heavy.Sword");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Roll, "InputTag.Roll");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SwitchTarget, "InputTag.SwitchTarget")

	UE_DEFINE_GAMEPLAY_TAG(InputTag_OnPressed, "InputTag.OnPressed");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_OnPressed_Block, "InputTag.OnPressed.Block");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable, "InputTag.Toggleable");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_LockOnOff, "InputTag.Toggleable.LockOnOff");
#pragma endregion

	// Player Tags //
#pragma region PlayerTag
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Sword, "Player.Weapon.Sword");

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Sword, "Player.Ability.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Sword, "Player.Ability.Unequip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Sword, "Player.Ability.Attack.Light.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Sword, "Player.Ability.Attack.Heavy.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitPause, "Player.Ability.HitPause");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Rolling, "Player.Ability.Rolling");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Block, "Player.Ability.Block");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_LockOnOff, "Player.Ability.LockOnOff");

	UE_DEFINE_GAMEPLAY_TAG(Player_Status_JumpToFinisher, "Player.Status.JumpToFinisher");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rolling, "Player.Status.Rolling");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Blocking, "Player.Status.Blocking");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Locking, "Player.Status.Locking");

	UE_DEFINE_GAMEPLAY_TAG(Player_Status_HitReact_Front, "Player.Status.HitReact.Front");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_HitReact_Back, "Player.Status.HitReact.Back");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_HitReact_Left, "Player.Status.HitReact.Left");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_HitReact_Right, "Player.Status.HitReact.Right");

	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_Attack_Light, "Player.SetByCaller.Attack.Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_Attack_Heavy, "Player.SetByCaller.Attack.Heavy");

	UE_DEFINE_GAMEPLAY_TAG(Player_TargetSwitch_ToAttacker, "Player.TargetSwitch.ToAttacker");
	UE_DEFINE_GAMEPLAY_TAG(Player_TargetSwitch_Left, "Player.TargetSwitch.Left");
	UE_DEFINE_GAMEPLAY_TAG(Player_TargetSwitch_Right, "Player.TargetSwitch.Right");

#pragma endregion

	// Enemy Tags //
#pragma region EnemyTag
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged, "Enemy.Ability.Ranged");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Strafing, "Enemy.Status.Strafing");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_UnderAttack, "Enemy.Status.UnderAttack");
#pragma endregion

	// Event Tags //
#pragma region EventTag
	UE_DEFINE_GAMEPLAY_TAG(Event_Equip_Sword, "Event.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Event_Unequip_Sword, "Event.Unequip.Sword");

	UE_DEFINE_GAMEPLAY_TAG(Event_Attack_Melee, "Event.Attack.Melee");

	UE_DEFINE_GAMEPLAY_TAG(Event_Block_Successed, "Event.Block.Successed");

	UE_DEFINE_GAMEPLAY_TAG(Event_Hit_Melee, "Event.Hit.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Event_Hit_React, "Event.Hit.React");
	UE_DEFINE_GAMEPLAY_TAG(Event_Hit_Pause, "Event.Hit.Pause");

	UE_DEFINE_GAMEPLAY_TAG(Event_Status_Death, "Event.Status.Death");
	
#pragma endregion

	// Shared Tags //
#pragma region SharedTag
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReaction, "Shared.Ability.HitReaction");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death");

	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage");
#pragma endregion
}
