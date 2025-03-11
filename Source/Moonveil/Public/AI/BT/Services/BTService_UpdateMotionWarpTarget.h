// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateMotionWarpTarget.generated.h"

class AMoonveilEnemyCharacter;

UCLASS()
class MOONVEIL_API UBTService_UpdateMotionWarpTarget : public UBTService
{
	GENERATED_BODY()

public:
#pragma region Interface
	//~ BTNode Interface
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticDescription() const;
#pragma endregion
	UBTService_UpdateMotionWarpTarget();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FBlackboardKeySelector InTargetActorKey;

protected:
	UPROPERTY(BlueprintReadOnly)
	AMoonveilEnemyCharacter* EnemyRef;
};
