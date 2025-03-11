// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "Components/MoonveilPawnExtensionComponent.h"
#include "MoonveilPawnUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatusPercentChangedDelegate, float, NewPercent);

UCLASS()
class MOONVEIL_API UMoonveilPawnUIComponent : public UMoonveilPawnExtensionComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnStatusPercentChangedDelegate OnCurrentHealthPercentChanged;
};
