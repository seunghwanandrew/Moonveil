// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MoonveilPlayerGameplayAbility.h"
#include "MoonveilPlayerGA_TargetLockOn.generated.h"

class UMoonveilUserWidgetBase;
class UInputMappingContext;

UCLASS()
class MOONVEIL_API UMoonveilPlayerGA_TargetLockOn : public UMoonveilPlayerGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);


protected:
	UFUNCTION(BlueprintCallable, Category = "LockOnAbility")
	void OnTickTask(float DeltaTime);
	UFUNCTION(BlueprintCallable, Category = "LockOnAbility")
	void SwitchTarget(const FGameplayTag& SwitchDirectionTag, AActor* Attacker);

	void InitIMC();
	void RemoveIMC();

	virtual void StartLockOn();
	virtual void GetPossibleLockOnTargets();
	AActor* GetNearestLockOnTarget(const TArray<AActor*>& PossibleTargetList);
	void GetAlerativeTargetListExceptCurrentTarget(TArray<AActor*>& OutTargetsOnLeft, TArray<AActor*>& OutTargetsOnRight);

	void DrawLockOnWidget();
	void SetLockOnWidgetOnTargetPosition();

	void CancelLockOnOffAbility();
	void Cleanup();

	void InitLockOnMovement();
	void ResetToDefaultMovement();

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* LockOnIMC;

	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	AActor* CurrentLockOnTarget;

	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	float LockOnMaxDistance = 1000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	float RotationInterpSpeed = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	float CameraOffset_Pitch = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	float LockOnMovementMaxSpeed = 250.0f;

	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	float DefaultMaxWalkSpeed = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	FVector TraceBoxSize = FVector(5000.0f, 5000.0f, 300.0f);

	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	TArray<TEnumAsByte<EObjectTypeQuery>> BoxTraceChannel;

	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	bool bDrawDebugTrace = false;

	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	TArray<AActor*> PossibleLockOnTargets;

	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	TSubclassOf<UMoonveilUserWidgetBase> LockOnWidget;

	UMoonveilUserWidgetBase* DrawnLockOnWidget;

	FVector2D LockOnWidgetSize = FVector2D::ZeroVector;
};
