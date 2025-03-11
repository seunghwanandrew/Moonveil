// Genesis : The World Creation
#include "Characters/MoonveilEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Combat/MoonveilEnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "DataAssets/StartUp/MoonveilBaseStartUpDataAsset.h"
#include "Components/UI/MoonveilEnemyUIComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/Widgets/MoonveilUserWidgetBase.h"

UMoonveilBaseCombatComponent* AMoonveilEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UMoonveilPawnUIComponent* AMoonveilEnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

UMoonveilEnemyUIComponent* AMoonveilEnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

AMoonveilEnemyCharacter::AMoonveilEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.0f;

	EnemyCombatComponent = CreateDefaultSubobject<UMoonveilEnemyCombatComponent>(TEXT("EnemyCombatComponent"));

	EnemyUIComponent = CreateDefaultSubobject<UMoonveilEnemyUIComponent>(TEXT("EnemyUIComponent"));

	EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHealthWidgetComponent"));
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());
}

void AMoonveilEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	Cast<UMoonveilUserWidgetBase>(EnemyHealthWidgetComponent->GetWidget())->InitEnemyCreatedWidget(this);
}

void AMoonveilEnemyCharacter::PossessedBy(AController* NewContrller)
{
	Super::PossessedBy(NewContrller);

	InitEnemyStartUpData();
}

void AMoonveilEnemyCharacter::InitEnemyStartUpData()
{
	if (StartUpData.IsNull()) return;

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		StartUpData.ToSoftObjectPath(), FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UMoonveilBaseStartUpDataAsset* LoadData = StartUpData.Get())
				{
					LoadData->GiveAbilityToAbilitySystemComponent(AbilitySystemComponent);
				}
			}
		)
	);
}
