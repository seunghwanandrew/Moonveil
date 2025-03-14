// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "MoonveilAbilityTask_OnTick.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityTickTaskDelegate, float, DeltaTime);

UCLASS()
class MOONVEIL_API UMoonveilAbilityTask_OnTick : public UAbilityTask
{

	GENERATED_BODY()

public:
	UMoonveilAbilityTask_OnTick();

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UMoonveilAbilityTask_OnTick* ExecuteOnTickTask(UGameplayAbility* OwningAbility);

	virtual void TickTask(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FOnAbilityTickTaskDelegate OnAbilityTickTask;
};
