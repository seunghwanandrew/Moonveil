// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_OrientDirectToTarget.generated.h"


UCLASS()
class MOONVEIL_API UBTService_OrientDirectToTarget : public UBTService
{
	GENERATED_BODY()
public:
#pragma region Interface
	//~ BTNode Interface
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticDescription() const;
#pragma endregion
	UBTService_OrientDirectToTarget();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "BlackboardKey")
	FBlackboardKeySelector InTargetActorKey;

	UPROPERTY(EditAnywhere, meta = (UIMin = "0.0", UIMax = "10.0"))
	float RotationInterSpeed;
};
