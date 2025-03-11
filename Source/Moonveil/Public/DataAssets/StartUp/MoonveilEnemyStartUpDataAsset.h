// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUp/MoonveilBaseStartUpDataAsset.h"
#include "MoonveilEnemyStartUpDataAsset.generated.h"

class UMoonveilEnemyGameplayAbility;

UCLASS()
class MOONVEIL_API UMoonveilEnemyStartUpDataAsset : public UMoonveilBaseStartUpDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void GiveAbilityToAbilitySystemComponent(UMoonveilAbilitySystemComponent* AbilitySystemComponentToGive, int32 ApplyLevel = 1) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|OnTriggered", meta = (TitleProperty = "AbilityInputTag"))
	TArray<TSubclassOf<UMoonveilEnemyGameplayAbility>> EnemyAbility;
};
