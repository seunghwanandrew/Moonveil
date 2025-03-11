// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUp/MoonveilBaseStartUpDataAsset.h"
#include "StructTypes/MoonveilStructTypes.h"
#include "MoonveilPlayerStartUpDataAsset.generated.h"


UCLASS()
class MOONVEIL_API UMoonveilPlayerStartUpDataAsset : public UMoonveilBaseStartUpDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void GiveAbilityToAbilitySystemComponent(UMoonveilAbilitySystemComponent* AbilitySystemComponentToGive, int32 ApplyLevel = 1) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|OnTriggered", meta = (TitleProperty = "AbilityInputTag"))
	TArray<FPlayerGameplayAbilitySet> PlayerAbilitySet;
};
