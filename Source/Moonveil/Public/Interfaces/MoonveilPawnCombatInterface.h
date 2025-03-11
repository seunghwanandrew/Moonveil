// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MoonveilPawnCombatInterface.generated.h"

class UMoonveilBaseCombatComponent;

UINTERFACE(MinimalAPI)
class UMoonveilPawnCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class MOONVEIL_API IMoonveilPawnCombatInterface
{
	GENERATED_BODY()

public:
	virtual UMoonveilBaseCombatComponent* GetPawnCombatComponent() const = 0;
};
