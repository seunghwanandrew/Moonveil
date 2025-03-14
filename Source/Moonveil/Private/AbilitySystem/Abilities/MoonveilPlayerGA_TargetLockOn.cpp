// Genesis : The World Creation
#include "AbilitySystem/Abilities/MoonveilPlayerGA_TargetLockOn.h"
#include "MoonveilDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/MoonveilPlayerCharacter.h"
#include "UI/Widgets/MoonveilUserWidgetBase.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "FunctionLibrary/MoonveilFunctionLibrary.h"
#include "GamePlayTags/MoonveilGameplayTags.h"
#include "Kismet/KismetMathLibrary.h"
#include "Controllers/MoonveilPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"

void UMoonveilPlayerGA_TargetLockOn::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	StartLockOn();
	InitLockOnMovement();

	InitIMC();
}

void UMoonveilPlayerGA_TargetLockOn::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	ResetToDefaultMovement();
	Cleanup();

	RemoveIMC();
}

void UMoonveilPlayerGA_TargetLockOn::OnTickTask(float DeltaTime)
{
	if (!CurrentLockOnTarget ||
		UMoonveilFunctionLibrary::NativeDoesActorHaveGameplayTag(CurrentLockOnTarget, FMoonveilGameplayTags::Event_Status_Death) ||
		UMoonveilFunctionLibrary::NativeDoesActorHaveGameplayTag(GetPlayerCharacterFromActorInfo(), FMoonveilGameplayTags::Event_Status_Death))
	{
		CancelLockOnOffAbility();
		return;
	}

	SetLockOnWidgetOnTargetPosition();

	const bool bShouldRotate = !UMoonveilFunctionLibrary::NativeDoesActorHaveGameplayTag(GetPlayerCharacterFromActorInfo(), FMoonveilGameplayTags::Player_Status_Rolling) ||
		!UMoonveilFunctionLibrary::NativeDoesActorHaveGameplayTag(GetPlayerCharacterFromActorInfo(), FMoonveilGameplayTags::Player_Status_Blocking);

	if (bShouldRotate)
	{
		FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetPlayerCharacterFromActorInfo()->GetActorLocation(), CurrentLockOnTarget->GetActorLocation());

		// Adjust Camera Location a Bit Upper
		LookAtRot -= FRotator(CameraOffset_Pitch, 0.0f, 0.0f);

		const FRotator CameraControlRot = GetPlayerControllerFromActorInfo()->GetControlRotation();
		const FRotator TargetRot = FMath::RInterpTo(CameraControlRot, LookAtRot, DeltaTime, RotationInterpSpeed);

		GetPlayerControllerFromActorInfo()->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.0f));
		GetPlayerCharacterFromActorInfo()->SetActorRotation(FRotator(0.0f, TargetRot.Yaw, 0.0f));
	}
}

void UMoonveilPlayerGA_TargetLockOn::SwitchTarget(const FGameplayTag& SwitchDirectionTag, AActor* Attacker)
{
	if (SwitchDirectionTag == FMoonveilGameplayTags::Player_TargetSwitch_ToAttacker)
	{
		CurrentLockOnTarget = Attacker;
	}
	else
	{
		GetPossibleLockOnTargets();

		TArray<AActor*> TargetsOnLeft;
		TArray<AActor*> TargetsOnRight;
		AActor* NewTarget = nullptr;

		GetAlerativeTargetListExceptCurrentTarget(TargetsOnLeft, TargetsOnRight);

		if (SwitchDirectionTag == FMoonveilGameplayTags::Player_TargetSwitch_Left)
		{
			NewTarget = GetNearestLockOnTarget(TargetsOnLeft);
		}
		else
		{
			NewTarget = GetNearestLockOnTarget(TargetsOnRight);
		}

		if (NewTarget)
		{
			CurrentLockOnTarget = NewTarget;
		}
	}
}

void UMoonveilPlayerGA_TargetLockOn::InitIMC()
{
	ULocalPlayer* LocalPlayer = GetPlayerControllerFromActorInfo()->GetLocalPlayer();
	if (LocalPlayer)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		Subsystem->AddMappingContext(LockOnIMC, 2);
	}
}

void UMoonveilPlayerGA_TargetLockOn::RemoveIMC()
{
	if (!GetPlayerControllerFromActorInfo())  return;
	ULocalPlayer* LocalPlayer = GetPlayerControllerFromActorInfo()->GetLocalPlayer();
	if (LocalPlayer)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		Subsystem->RemoveMappingContext(LockOnIMC);
	}
}

void UMoonveilPlayerGA_TargetLockOn::StartLockOn()
{
	GetPossibleLockOnTargets();

	if (PossibleLockOnTargets.IsEmpty())
	{
		CancelLockOnOffAbility();
		return;
	}

	CurrentLockOnTarget = GetNearestLockOnTarget(PossibleLockOnTargets);

	if (CurrentLockOnTarget)
	{
		DrawLockOnWidget();
		SetLockOnWidgetOnTargetPosition();
	}
	else
	{
		CancelLockOnOffAbility();
	}
}

void UMoonveilPlayerGA_TargetLockOn::GetPossibleLockOnTargets()
{
	TArray<FHitResult> OutHits;
	FVector TraceStartFrom = GetPlayerCharacterFromActorInfo()->GetActorLocation();
	FVector TraceEndTo = TraceStartFrom + GetPlayerCharacterFromActorInfo()->GetActorForwardVector() * LockOnMaxDistance;
	FRotator Orientation = GetPlayerCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator();

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetWorld(), TraceStartFrom, TraceEndTo, TraceBoxSize * 0.5f, Orientation, BoxTraceChannel, false,
		TArray<AActor*>(), bDrawDebugTrace ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None, OutHits, true);

	for (const FHitResult& Hit : OutHits)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			if (HitActor != GetPlayerCharacterFromActorInfo())
			{
				PossibleLockOnTargets.AddUnique(HitActor);
			}
		}
	}
}

AActor* UMoonveilPlayerGA_TargetLockOn::GetNearestLockOnTarget(const TArray<AActor*>& PossibleTargetList)
{
	FVector PlayerLocation = GetPlayerCharacterFromActorInfo()->GetActorLocation();
	AActor* NearestActor = nullptr;
	float NearestActorDistance = TNumericLimits<float>::Max();

	for (AActor* ActorToCheck : PossibleTargetList)
	{
		if (ActorToCheck)
		{
			const float DistanceFromActorToCheck = (PlayerLocation - ActorToCheck->GetActorLocation()).SizeSquared();
			if (DistanceFromActorToCheck < NearestActorDistance)
			{
				NearestActor = ActorToCheck;
				NearestActorDistance = DistanceFromActorToCheck;
			}
		}
	}

	return NearestActor;
}

void UMoonveilPlayerGA_TargetLockOn::GetAlerativeTargetListExceptCurrentTarget(TArray<AActor*>& OutTargetsOnLeft, TArray<AActor*>& OutTargetsOnRight)
{
	if (!CurrentLockOnTarget || PossibleLockOnTargets.IsEmpty())
	{
		CancelLockOnOffAbility();
		return;
	}

	const FVector PlayerCurrentLocation = GetPlayerCharacterFromActorInfo()->GetActorLocation();
	const FVector PlayerToCurrentTargetNormalizedVector = (CurrentLockOnTarget->GetActorLocation() - PlayerCurrentLocation).GetSafeNormal();

	for (AActor* TargetToCheck : PossibleLockOnTargets)
	{
		if (TargetToCheck == CurrentLockOnTarget) continue;

		const FVector PlayerToTargetNormalizedVector = (TargetToCheck->GetActorLocation() - PlayerCurrentLocation).GetSafeNormal();

		const FVector CrossProduct = FVector::CrossProduct(PlayerToCurrentTargetNormalizedVector, PlayerToTargetNormalizedVector);

		if (CrossProduct.Z > 0.0f)
		{
			OutTargetsOnRight.AddUnique(TargetToCheck);
		}
		else
		{
			OutTargetsOnLeft.AddUnique(TargetToCheck);
		}
	}
}

void UMoonveilPlayerGA_TargetLockOn::DrawLockOnWidget()
{
	if (LockOnWidget)
	{
		DrawnLockOnWidget = CreateWidget<UMoonveilUserWidgetBase>(GetPlayerControllerFromActorInfo(), LockOnWidget);
		if (DrawnLockOnWidget)
		{
			DrawnLockOnWidget->AddToViewport();
		}
	}
}

void UMoonveilPlayerGA_TargetLockOn::SetLockOnWidgetOnTargetPosition()
{
	if (!DrawnLockOnWidget || !CurrentLockOnTarget)
	{
		CancelLockOnOffAbility();
		return;
	}

	FVector2D ScreenPosition;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(Cast<APlayerController>(GetPlayerControllerFromActorInfo()), CurrentLockOnTarget->GetActorLocation(), ScreenPosition, true);

	if (LockOnWidgetSize == FVector2D::ZeroVector)
	{
		DrawnLockOnWidget->WidgetTree->ForEachWidget(
			[this](UWidget* Widget)
			{
				if (USizeBox* WidgetSize = Cast<USizeBox>(Widget))
				{
					LockOnWidgetSize.X = WidgetSize->GetWidthOverride();
					LockOnWidgetSize.Y = WidgetSize->GetHeightOverride();
				}
			}
		);
	}

	ScreenPosition -= LockOnWidgetSize * 0.5f;

	DrawnLockOnWidget->SetPositionInViewport(ScreenPosition, false);
}

void UMoonveilPlayerGA_TargetLockOn::CancelLockOnOffAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);

	Cleanup();
}

void UMoonveilPlayerGA_TargetLockOn::Cleanup()
{
	PossibleLockOnTargets.Empty();
	CurrentLockOnTarget = nullptr;
	if (DrawnLockOnWidget)
	{
		DrawnLockOnWidget->RemoveFromParent();
	}
	DrawnLockOnWidget = nullptr;
	LockOnWidgetSize = FVector2D::ZeroVector;
}

void UMoonveilPlayerGA_TargetLockOn::InitLockOnMovement()
{
	DefaultMaxWalkSpeed = GetPlayerCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed;
	GetPlayerCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = LockOnMovementMaxSpeed;
}

void UMoonveilPlayerGA_TargetLockOn::ResetToDefaultMovement()
{
	if (DefaultMaxWalkSpeed > 0.0f)
	{
		GetPlayerCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed;
		DefaultMaxWalkSpeed = 0.0f;
	}
}

