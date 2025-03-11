// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_GetDistanceToActor.generated.h"

UCLASS()
class MOONVEIL_API UBTService_GetDistanceToActor : public UBTService
{
	GENERATED_BODY()
	
public:
#pragma region Interfaces
	//~ BTNode Interface
	virtual void InitializeFromAsset(UBehaviorTree& Asset);
	virtual FString GetStaticDescription() const;
#pragma endregion
	UBTService_GetDistanceToActor();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "BlackboardKey")
	FBlackboardKeySelector InTargetActorKey;
	UPROPERTY(EditAnywhere, Category = "BlackboardKey")
	FBlackboardKeySelector OutDistToTargetKey;
};
