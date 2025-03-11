// Genesis : The World Creation

#pragma once

#include "CoreMinimal.h"
#include "AI/BT/Tasks/BTTask_EnemyBase.h"
#include "GameplayTagContainer.h"
#include "BTTask_ActivateAbilityByTag.generated.h"


UCLASS()
class MOONVEIL_API UBTTask_ActivateAbilityByTag : public UBTTask_EnemyBase
{
	GENERATED_BODY()
	
public:
	UBTTask_ActivateAbilityByTag();
	virtual FString GetStaticDescription() const override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnEnemyExecuteTask(UBehaviorTreeComponent& OwnerComp, AMoonveilEnemyCharacter* EnemyRef) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag AbilityTagToActivate;
};
