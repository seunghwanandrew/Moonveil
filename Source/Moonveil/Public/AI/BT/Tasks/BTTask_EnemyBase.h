// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_EnemyBase.generated.h"

class AMoonveilEnemyCharacter;

struct FEnemyBaseMemory
{
	TWeakObjectPtr<AMoonveilEnemyCharacter> EnemyCharacterRef;

	bool IsValid() const
	{
		return EnemyCharacterRef.IsValid();
	}

	void Reset()
	{
		EnemyCharacterRef.Reset();
	}
};

UCLASS()
class MOONVEIL_API UBTTask_EnemyBase : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_EnemyBase();
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticDescription() const override;
	virtual uint16 GetInstanceMemorySize() const override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnEnemyExecuteTask(UBehaviorTreeComponent& OwnerComp, AMoonveilEnemyCharacter* EnemyRef);
};
