// Genesis : The World Creation
#include "Characters/MoonveilPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/MoonveilInputConfigDataAsset.h"
#include "Components/Input/MoonveilEnhancedInputComponent.h"
#include "GamePlayTags/MoonveilGameplayTags.h"
#include "DataAssets/StartUp/MoonveilPlayerStartUpDataAsset.h"
#include "Components/Combat/MoonveilPlayerCombatComponent.h"
#include "AbilitySystem/MoonveilAbilitySystemComponent.h"
#include "Components/UI/MoonveilPlayerUIComponent.h"

UMoonveilBaseCombatComponent* AMoonveilPlayerCharacter::GetPawnCombatComponent() const
{
	return PlayerCombatComponent;
}

UMoonveilPawnUIComponent* AMoonveilPlayerCharacter::GetPawnUIComponent() const
{
	return PlayerUIComponent;
}

UMoonveilPlayerUIComponent* AMoonveilPlayerCharacter::GetPlayerUIComponent() const
{
	return PlayerUIComponent;
}

AMoonveilPlayerCharacter::AMoonveilPlayerCharacter()
{
	GetCapsuleComponent()->SetCapsuleSize(42.0f, 96.0f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 55.0f, 65.0f);

	FollowingCam = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowingCam"));
	FollowingCam->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowingCam->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	PlayerCombatComponent = CreateDefaultSubobject<UMoonveilPlayerCombatComponent>(TEXT("PlayerCombatComponent"));

	PlayerUIComponent = CreateDefaultSubobject<UMoonveilPlayerUIComponent>(TEXT("PlayerUIComponent"));
}

void AMoonveilPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer())
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

		if (Subsystem)
		{
			Subsystem->AddMappingContext(InputConfigData->DefaultInputMappingContext, 0);
		}
	}

	UMoonveilEnhancedInputComponent* EnhancedInputComponent = CastChecked<UMoonveilEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindNativeInputAction(InputConfigData, FMoonveilGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &AMoonveilPlayerCharacter::Input_Move);
	EnhancedInputComponent->BindNativeInputAction(InputConfigData, FMoonveilGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &AMoonveilPlayerCharacter::Input_Look);
	EnhancedInputComponent->BindAbilityInputAction(InputConfigData, this, &AMoonveilPlayerCharacter::Input_AbilityOnPressed, &AMoonveilPlayerCharacter::Input_AbilityOnReleased);
}

void AMoonveilPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMoonveilPlayerCharacter::PossessedBy(AController* NewContrller)
{
	Super::PossessedBy(NewContrller);

	UMoonveilBaseStartUpDataAsset* LoadData = StartUpData.LoadSynchronous();
	if (LoadData)
	{
		LoadData->GiveAbilityToAbilitySystemComponent(AbilitySystemComponent);
	}
}

void AMoonveilPlayerCharacter::Input_Move(const FInputActionValue& InputValue)
{
	const FVector2D MoveDirection = InputValue.Get<FVector2D>();
	
	if (GetController())
	{
		const FRotator YawRotation = FRotator(0.0f, GetController()->GetControlRotation().Yaw, 0.0f);
		const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardVector, MoveDirection.Y);
		const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightVector, MoveDirection.X);
	}
}

void AMoonveilPlayerCharacter::Input_Look(const FInputActionValue& InputValue)
{
	const FVector2D LookAxisVector = InputValue.Get<FVector2D>();

	if (GetController())
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMoonveilPlayerCharacter::Input_AbilityOnPressed(FGameplayTag AbilityInputTag)
{
	AbilitySystemComponent->TagAbilityOnPressed(AbilityInputTag);
}

void AMoonveilPlayerCharacter::Input_AbilityOnReleased(FGameplayTag AbilityInputTag)
{
	AbilitySystemComponent->TagAbilityOnReleased(AbilityInputTag);
}
