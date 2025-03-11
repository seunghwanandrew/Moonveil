// Genesis : The World Creation
#include "Characters/MoonveilBaseCharacter.h"
#include "AbilitySystem/MoonveilAbilitySystemComponent.h"
#include "AbilitySystem/MoonveilAttributeSet.h"
#include "MotionWarpingComponent.h"

UAbilitySystemComponent* AMoonveilBaseCharacter::GetAbilitySystemComponent() const
{
	return GetCharacterAbilitySystemComponent();
}

UMoonveilBaseCombatComponent* AMoonveilBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

UMoonveilPawnUIComponent* AMoonveilBaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}

AMoonveilBaseCharacter::AMoonveilBaseCharacter()
{

	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	AbilitySystemComponent = CreateDefaultSubobject<UMoonveilAbilitySystemComponent>(TEXT("MoonveilAbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UMoonveilAttributeSet>(TEXT("MoonveilAttributeSet"));
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping"));
}

void AMoonveilBaseCharacter::PossessedBy(AController* NewContrller)
{
	Super::PossessedBy(NewContrller);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!StartUpData.IsNull(), TEXT("Invalid Data. Please Check Assignment of StartUp Data Asset."));
	}
}