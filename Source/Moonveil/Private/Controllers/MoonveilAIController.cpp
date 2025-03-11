// Genesis : The World Creation
#include "Controllers/MoonveilAIController.h"
#include "Navigation/CrowdFollowingComponent.h" 
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "GenericTeamAgentInterface.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/MoonveilBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "MoonveilDebugHelpers.h"

ETeamAttitude::Type AMoonveilAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* TargetPawn = Cast<const APawn>(&Other);

	if (TargetPawn->GetController() && TargetPawn->GetController()->Implements<UGenericTeamAgentInterface>())
	{
		const IGenericTeamAgentInterface* TargetPawnTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

		if (TargetPawnTeamAgent->GetGenericTeamId() < GetGenericTeamId())
		{
			return ETeamAttitude::Hostile;
		}
	}

	return ETeamAttitude::Friendly;
}

void AMoonveilAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!BehaviorTreeAsset) return;

	RunBehaviorTree(BehaviorTreeAsset);

	GetBlackboardComponent()->SetValueAsFloat(FName(TEXT("DefaultMaxWalkSpeed")), Cast<AMoonveilBaseCharacter>(InPawn)->GetCharacterMovement()->MaxWalkSpeed);
}

AMoonveilAIController::AMoonveilAIController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(FName(TEXT("PathFollowingComponent"))))
{
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfig_Sight"));
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfig_Sight->SightRadius = 5000.0f;
	AISenseConfig_Sight->LoseSightRadius = 0.0f;
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 360.0f;

	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("EnemyPerceptionComponent"));
	EnemyPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());

	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AMoonveilAIController::OnEnemyPerceptionUpdated);

	SetGenericTeamId(1);
}

void AMoonveilAIController::BeginPlay()
{
	Super::BeginPlay();

	UCrowdFollowingComponent* CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent());
	if (!CrowdFollowingComponent) return;

	CrowdFollowingComponent->SetCrowdSimulationState(bEnableDetourCrowdAvoidance ? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);

	switch (DetourCrowdAvoidanceQuailityLevel)
	{
	case 1: CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);		break;
	case 2: CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);	break;
	case 3: CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);	break;
	case 4: CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);	break;
	default: break;
	}

	CrowdFollowingComponent->SetCrowdCollisionQueryRange(CollisionQueryRange);
	CrowdFollowingComponent->SetAvoidanceGroup(1);
	CrowdFollowingComponent->SetGroupsToAvoid(1);
}

void AMoonveilAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	if (!BlackboardComponent) return;

	if (!BlackboardComponent->GetValueAsObject("TargetActor"))
	{
		if (Stimulus.WasSuccessfullySensed() && Actor)
		{
			BlackboardComponent->SetValueAsObject("TargetActor", Actor);
		}
	}	
}
