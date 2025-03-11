// Genesis : The World Creation

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/MoonveilPawnUIComponent.h"
#include "MoonveilPlayerUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedWeaponEquippedStateDelegate, TSoftObjectPtr<UTexture2D>, SoftWeaponIconTexture);

UCLASS()
class MOONVEIL_API UMoonveilPlayerUIComponent : public UMoonveilPawnUIComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnStatusPercentChangedDelegate OnCurrentRagePercentChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnChangedWeaponEquippedStateDelegate OnChangedWeaponEquippedState;
};
