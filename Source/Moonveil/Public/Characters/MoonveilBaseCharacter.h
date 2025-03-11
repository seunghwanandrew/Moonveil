// Genesis : The World Creation

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/MoonveilPawnCombatInterface.h"
#include "Interfaces/MoonveilPawnUIInterface.h"
#include "MoonveilBaseCharacter.generated.h"

class UMoonveilAbilitySystemComponent;
class UAttributeSet;
class UMoonveilBaseStartUpDataAsset;
class UMotionWarpingComponent;

UCLASS()
class MOONVEIL_API AMoonveilBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IMoonveilPawnCombatInterface, public IMoonveilPawnUIInterface
{
	GENERATED_BODY()

public:
#pragma region Getter
	FORCEINLINE UMoonveilAbilitySystemComponent* GetCharacterAbilitySystemComponent() const { return AbilitySystemComponent; }
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	FORCEINLINE UMotionWarpingComponent* GetMotionWarpingComponent() const { return MotionWarpingComponent; }
#pragma endregion
#pragma region Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UMoonveilBaseCombatComponent* GetPawnCombatComponent() const override;
	virtual UMoonveilPawnUIComponent* GetPawnUIComponent() const override;
#pragma endregion
	AMoonveilBaseCharacter();
	virtual void PossessedBy(AController* NewContrller) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|AbilitySystem")
	UMoonveilAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|AbilitySystem")
	UAttributeSet* AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|MotionWarping")
	UMotionWarpingComponent* MotionWarpingComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataAssets|StartUp")
	TSoftObjectPtr<UMoonveilBaseStartUpDataAsset> StartUpData;
};
