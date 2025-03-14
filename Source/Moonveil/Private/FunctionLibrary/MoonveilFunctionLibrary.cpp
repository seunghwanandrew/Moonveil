// Genesis : The World Creation
#include "FunctionLibrary/MoonveilFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/MoonveilAbilitySystemComponent.h"
#include "Interfaces/MoonveilPawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "GamePlayTags/MoonveilGameplayTags.h"

#include "MoonveilDebugHelpers.h"

UMoonveilAbilitySystemComponent* UMoonveilFunctionLibrary::NativeGetAbilitySystemComponentFromActor(AActor* Actor)
{
    return CastChecked<UMoonveilAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor));
}


UMoonveilAbilitySystemComponent* UMoonveilFunctionLibrary::BP_GetAbilitySystemComponentFromActor(AActor* Actor)
{
    return NativeGetAbilitySystemComponentFromActor(Actor);
}


void UMoonveilFunctionLibrary::AddGameplayTagToActorIfNone(AActor* Actor, FGameplayTag TagToAdd)
{
    UMoonveilAbilitySystemComponent* AbilitySystemComponent = NativeGetAbilitySystemComponentFromActor(Actor);

    if (AbilitySystemComponent)
    {
        if (!AbilitySystemComponent->HasMatchingGameplayTag(TagToAdd))
        {
            AbilitySystemComponent->AddLooseGameplayTag(TagToAdd);
        }
    }
}

void UMoonveilFunctionLibrary::RemoveGameplayTagFromActorIfHas(AActor* Actor, FGameplayTag TagToRemove)
{
    UMoonveilAbilitySystemComponent* AbilitySystemComponent = NativeGetAbilitySystemComponentFromActor(Actor);

    if (AbilitySystemComponent)
    {
        if (AbilitySystemComponent->HasMatchingGameplayTag(TagToRemove))
        {
            AbilitySystemComponent->RemoveLooseGameplayTag(TagToRemove);
        }
    }
}

bool UMoonveilFunctionLibrary::NativeDoesActorHaveGameplayTag(AActor* Actor, FGameplayTag TagToCheck)
{
    UMoonveilAbilitySystemComponent* AbilitySystemComponent = NativeGetAbilitySystemComponentFromActor(Actor);

    if (AbilitySystemComponent->HasMatchingGameplayTag(TagToCheck))
    {
        return true;
    }

    return false;
}

void UMoonveilFunctionLibrary::BP_DoesActorHaveGameplayTag(AActor* Actor, FGameplayTag TagToCheck, EConfirmType& OutConfirmType)
{
    OutConfirmType = NativeDoesActorHaveGameplayTag(Actor, TagToCheck) ? EConfirmType::Yes : EConfirmType::No;
}

UMoonveilBaseCombatComponent* UMoonveilFunctionLibrary::NativeGetPawnCombatComponent(AActor* Actor)
{
    if (Actor->Implements<UMoonveilPawnCombatInterface>())
    {
        IMoonveilPawnCombatInterface* PawnCombatInterface = Cast<IMoonveilPawnCombatInterface>(Actor);
        return PawnCombatInterface->GetPawnCombatComponent();
    }

    return nullptr;
}

UMoonveilBaseCombatComponent* UMoonveilFunctionLibrary::BP_GetPawnCombatComponent(AActor* Actor, EValidType& OutValidType)
{
    UMoonveilBaseCombatComponent* PawnCombatComponent = NativeGetPawnCombatComponent(Actor);

    OutValidType = PawnCombatComponent ? EValidType::Valid : EValidType::InValid;

    return PawnCombatComponent;
}

bool UMoonveilFunctionLibrary::IsTargetPawnHostile(APawn* Query, APawn* Target)
{
    check(Query && Target);

    if (Query->GetController()->Implements<UGenericTeamAgentInterface>() && Target->GetController()->Implements<UGenericTeamAgentInterface>())
    {
        FGenericTeamId QueryTeamId = Cast<IGenericTeamAgentInterface>(Query->GetController())->GetGenericTeamId();
        FGenericTeamId TargetTeamId = Cast<IGenericTeamAgentInterface>(Target->GetController())->GetGenericTeamId();
        return QueryTeamId != TargetTeamId;
    }

    return false;
}

float UMoonveilFunctionLibrary::GetFloatValueFromScalableFloatAtLevel(const FScalableFloat& ScalableFloat, int32 ApplyLevel)
{
    return ScalableFloat.GetValueAtLevel(ApplyLevel);
}

FGameplayTag UMoonveilFunctionLibrary::ComputeHitReactDirectionTag(AActor* Attacker, AActor* Target, float& OutDifferences)
{
	if (!Attacker || !Target) return FGameplayTag();

	FVector AttackerLocation = Attacker->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();
	FVector HitFromNormalizedDirection = (AttackerLocation - TargetLocation).GetSafeNormal();
	FVector TargetForward = Target->GetActorForwardVector();

	const float DotResult = FVector::DotProduct(TargetForward, HitFromNormalizedDirection);
	OutDifferences = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(TargetForward, HitFromNormalizedDirection);

    if (CrossResult.Z < 0.0f)
    {
        OutDifferences *= -1.0f;
    }

    FGameplayTag HitFromDirectionTag = FMoonveilGameplayTags::Player_Status_HitReact_Front;

	if (OutDifferences < -45.0f && OutDifferences >= -135.0f) { HitFromDirectionTag = FMoonveilGameplayTags::Player_Status_HitReact_Left; }
	else if (OutDifferences < -135.0f || OutDifferences > 135.0f) { HitFromDirectionTag = FMoonveilGameplayTags::Player_Status_HitReact_Back; }
	else if (OutDifferences <= 135.0f && OutDifferences > 45.0f) { HitFromDirectionTag = FMoonveilGameplayTags::Player_Status_HitReact_Right; }

	return HitFromDirectionTag;
}

bool UMoonveilFunctionLibrary::IsValidBlock(AActor* Attacker, AActor* Target)
{
	if (!Attacker || !Target) return false;

	FVector AttackerForwardVector = Attacker->GetActorForwardVector();
	FVector TargetForwardVector = Target->GetActorForwardVector();

	float DotResult = FVector::DotProduct(AttackerForwardVector, TargetForwardVector);

    return DotResult < -0.1f;
}
