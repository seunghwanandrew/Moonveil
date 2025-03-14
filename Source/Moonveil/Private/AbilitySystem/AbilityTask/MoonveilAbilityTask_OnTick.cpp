// Genesis : The World Creation
#include "AbilitySystem/AbilityTask/MoonveilAbilityTask_OnTick.h"

UMoonveilAbilityTask_OnTick::UMoonveilAbilityTask_OnTick()
{
	bTickingTask = true;
}

UMoonveilAbilityTask_OnTick* UMoonveilAbilityTask_OnTick::ExecuteOnTickTask(UGameplayAbility* OwningAbility)
{
	UMoonveilAbilityTask_OnTick* Node = NewAbilityTask<UMoonveilAbilityTask_OnTick>(OwningAbility);
	return Node;
}

void UMoonveilAbilityTask_OnTick::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnAbilityTickTask.Broadcast(DeltaTime);
	}
	else
	{
		EndTask();
	}
}
