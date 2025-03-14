// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "Characters/MoonveilBaseCharacter.h"
#include "GameplayTagContainer.h"
#include "MoonveilPlayerCharacter.generated.h"

class UMoonveilInputConfigDataAsset;
struct FInputActionValue;
class UMoonveilPlayerCombatComponent;
class UMoonveilPlayerUIComponent;

UCLASS()
class MOONVEIL_API AMoonveilPlayerCharacter : public AMoonveilBaseCharacter
{
	GENERATED_BODY()
	
public:
#pragma region Getter
	FORCEINLINE UMoonveilPlayerCombatComponent* GetPlayerCombatComponent() const { return PlayerCombatComponent; }
#pragma endregion
#pragma region Interface
	virtual UMoonveilBaseCombatComponent* GetPawnCombatComponent() const override;
	virtual UMoonveilPawnUIComponent* GetPawnUIComponent() const override;
	virtual UMoonveilPlayerUIComponent* GetPlayerUIComponent() const override;
#pragma endregion
	AMoonveilPlayerCharacter();

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewContrller) override;

private:
	void Input_Move(const FInputActionValue& InputValue);
	void Input_Look(const FInputActionValue& InputValue);

	void Input_AbilityOnPressed(FGameplayTag AbilityInputTag);
	void Input_AbilityOnReleased(FGameplayTag AbilityInputTag);

	void Input_SwitchTargetTriggered(const FInputActionValue& InputValue);
	void Input_SwitchTargetCompleted(const FInputActionValue& InputValue);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowingCam;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|Combat", meta = (AllowPrivateAccess = "true"))
	UMoonveilPlayerCombatComponent* PlayerCombatComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|UI", meta = (AllowPrivateAccess = "true"))
	UMoonveilPlayerUIComponent* PlayerUIComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataAssets|Input", meta = (AllowPrivateAccess = "true"))
	UMoonveilInputConfigDataAsset* InputConfigData;

	FVector2D SwitchDirection = FVector2D::ZeroVector;
};
