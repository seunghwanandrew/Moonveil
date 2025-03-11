// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "Characters/MoonveilBaseCharacter.h"
#include "MoonveilEnemyCharacter.generated.h"

class UMoonveilEnemyCombatComponent;
class UMoonveilEnemyUIComponent;
class UWidgetComponent;

UCLASS()
class MOONVEIL_API AMoonveilEnemyCharacter : public AMoonveilBaseCharacter
{
	GENERATED_BODY()

public:
#pragma region Getter
	FORCEINLINE UMoonveilEnemyCombatComponent* GetEnemyCombatComponent() { return EnemyCombatComponent; }
#pragma endregion
#pragma region Interface
	virtual UMoonveilBaseCombatComponent* GetPawnCombatComponent() const override;
	virtual UMoonveilPawnUIComponent* GetPawnUIComponent() const override;
	virtual UMoonveilEnemyUIComponent* GetEnemyUIComponent() const override;
#pragma endregion
	AMoonveilEnemyCharacter();
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewContrller) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|Combat")
	UMoonveilEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|UI")
	UMoonveilEnemyUIComponent* EnemyUIComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|UI")
	UWidgetComponent* EnemyHealthWidgetComponent;

private:
	void InitEnemyStartUpData();
};
