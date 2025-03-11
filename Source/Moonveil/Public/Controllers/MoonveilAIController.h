// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MoonveilAIController.generated.h"

class UAISenseConfig_Sight;
class UBehaviorTree;
struct FAIStimulus;

UCLASS()
class MOONVEIL_API AMoonveilAIController : public AAIController
{
	GENERATED_BODY()
	
public:
#pragma region Interface
	// IGenericeTeamAgent Interface
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const;
	// AController Interface
	virtual void OnPossess(APawn* InPawn) override;
#pragma endregion
	AMoonveilAIController(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintCallable)
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Components")
	UAIPerceptionComponent* EnemyPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Components")
	UAISenseConfig_Sight* AISenseConfig_Sight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI Components")
	UBehaviorTree* BehaviorTreeAsset;

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI Components|Detour Crowd Avoidance Config")
	bool bEnableDetourCrowdAvoidance = true;

	UPROPERTY(EditDefaultsOnly, Category = "AI Components|Detour Crowd Avoidance Config", meta = (EditCondition = "bEnableDetourCrowdAvoidance", UIMin = "1", UIMax = "4"))
	int32 DetourCrowdAvoidanceQuailityLevel = 4;

	UPROPERTY(EditDefaultsOnly, Category = "AI Components|Detour Crowd Avoidance Config", meta = (EditCondition = "bEnableDetourCrowdAvoidance"))
	float CollisionQueryRange = 600.0f;
};
