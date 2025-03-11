// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/MoonveilAbilitySystemComponent.h"
#include "MoonveilAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class IMoonveilPawnUIInterface;

UCLASS()
class MOONVEIL_API UMoonveilAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UMoonveilAttributeSet();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

#pragma region Attribute Stats
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UMoonveilAttributeSet, CurrentHealth);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMoonveilAttributeSet, MaxHealth);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|Rage")
	FGameplayAttributeData CurrentRage;
	ATTRIBUTE_ACCESSORS(UMoonveilAttributeSet, CurrentRage);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|Rage")
	FGameplayAttributeData MaxRage;
	ATTRIBUTE_ACCESSORS(UMoonveilAttributeSet, MaxRage);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|AttackPower")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UMoonveilAttributeSet, AttackPower);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|DefensePower")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UMoonveilAttributeSet, DefensePower);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|DamageTaken")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UMoonveilAttributeSet, DamageTaken);
#pragma endregion

protected:
	TWeakInterfacePtr<IMoonveilPawnUIInterface> PawnUIInterfaceRef;

private:
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bDebugMode = false;
};
