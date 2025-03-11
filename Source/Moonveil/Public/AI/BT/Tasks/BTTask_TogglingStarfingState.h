// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "AI/BT/Tasks/BTTask_EnemyBase.h"
#include "BTTask_TogglingStarfingState.generated.h"


UCLASS()
class MOONVEIL_API UBTTask_TogglingStarfingState : public UBTTask_EnemyBase
{
	GENERATED_BODY()	

public:
	UBTTask_TogglingStarfingState();
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticDescription() const;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnEnemyExecuteTask(UBehaviorTreeComponent& OwnerComp, AMoonveilEnemyCharacter* EnemyRef);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bShouldEnableStrafingState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bShouldChangeWalkMaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "10000.0"))
	float StrafingMaxWalkSpeed;
};
