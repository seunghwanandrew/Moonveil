// Genesis : The World Creation
#include "AbilitySystem/Abilities/GameplayEffectExcutionCalculation/Moonveil_GE_ExecCalcDamageHandle.h"
#include "AbilitySystem/MoonveilAttributeSet.h"
#include "GamePlayTags/MoonveilGameplayTags.h"

#include "MoonveilDebugHelpers.h"

struct FMoonveilDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken);

	FMoonveilDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMoonveilAttributeSet, AttackPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMoonveilAttributeSet, DefensePower, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMoonveilAttributeSet, DamageTaken, Target, false);
	}
};

static const FMoonveilDamageCapture& GetMoonveilDamageCapture()
{
	static FMoonveilDamageCapture FMoonveilDamageCapture;
	return FMoonveilDamageCapture;
}

UMoonveil_GE_ExecCalcDamageHandle::UMoonveil_GE_ExecCalcDamageHandle()
{
	RelevantAttributesToCapture.Add(GetMoonveilDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetMoonveilDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetMoonveilDamageCapture().DamageTakenDef);
}

void UMoonveil_GE_ExecCalcDamageHandle::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParams.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetMoonveilDamageCapture().AttackPowerDef, EvaluateParams, SourceAttackPower);

	float BaseDamage = 0.0f;
	int32 CurrentLightAttackComboCount = 0;
	int32 CurrentHeavyAttackComboCount = 0;

	for (const TPair <FGameplayTag, float> TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(FMoonveilGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
		}

		if (TagMagnitude.Key.MatchesTagExact(FMoonveilGameplayTags::Player_SetByCaller_Attack_Light))
		{
			CurrentLightAttackComboCount = TagMagnitude.Value;
		}

		if (TagMagnitude.Key.MatchesTagExact(FMoonveilGameplayTags::Player_SetByCaller_Attack_Heavy))
		{
			CurrentHeavyAttackComboCount = TagMagnitude.Value;
		}
	}

	float TargetDefensePower = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetMoonveilDamageCapture().DefensePowerDef, EvaluateParams, TargetDefensePower);

	if (CurrentLightAttackComboCount != 0)
	{
		const float LightDamageIncreasementPercent = (CurrentLightAttackComboCount - 1) * 0.05 + 1.0f;

		BaseDamage *= LightDamageIncreasementPercent;
	}

	if (CurrentHeavyAttackComboCount != 0)
	{
		const float HeavyDamageIncreasementPercent = CurrentHeavyAttackComboCount * 0.15 + 1.0f;

		BaseDamage *= HeavyDamageIncreasementPercent;
	}

	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;

	if (FinalDamageDone > 0.0f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetMoonveilDamageCapture().DamageTakenProperty, EGameplayModOp::Override, FinalDamageDone));
	}
}
