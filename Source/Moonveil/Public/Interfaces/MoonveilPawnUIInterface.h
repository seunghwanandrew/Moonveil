// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MoonveilPawnUIInterface.generated.h"

class UMoonveilPawnUIComponent;
class UMoonveilPlayerUIComponent;
class UMoonveilEnemyUIComponent;

UINTERFACE(MinimalAPI)
class UMoonveilPawnUIInterface : public UInterface
{
	GENERATED_BODY()
};

class MOONVEIL_API IMoonveilPawnUIInterface
{
	GENERATED_BODY()

public:
	virtual UMoonveilPawnUIComponent* GetPawnUIComponent() const = 0;
	virtual UMoonveilPlayerUIComponent* GetPlayerUIComponent() const;
	virtual UMoonveilEnemyUIComponent* GetEnemyUIComponent() const;
};
