// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/MoonveilBaseCombatComponent.h"
#include "MoonveilEnemyCombatComponent.generated.h"


UCLASS()
class MOONVEIL_API UMoonveilEnemyCombatComponent : public UMoonveilBaseCombatComponent
{
	GENERATED_BODY()


protected:
	virtual void TargetOnWeapon(AActor* Target) override;
	virtual void TargetOffWeapon(AActor* Target) override;
};
