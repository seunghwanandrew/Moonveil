// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "Items/Weapon/MoonveilBaseWeapon.h"
#include "StructTypes/MoonveilStructTypes.h"
#include "MoonveilPlayerWeapon.generated.h"

UCLASS()
class MOONVEIL_API AMoonveilPlayerWeapon : public AMoonveilBaseWeapon
{
	GENERATED_BODY()
	
public:
#pragma region Getter
	FORCEINLINE FWeaponData GetWeaponData() { return WeaponData; }
#pragma endregion

	UFUNCTION(BlueprintCallable, Category = "AbilitySpecHandle")
	void AssignActivatedAbilitySpecHandle(const TArray<FGameplayAbilitySpecHandle>& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "AbilitySpecHandle")
	TArray<FGameplayAbilitySpecHandle> GetActivatedAbilitySpecHandle();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FWeaponData WeaponData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	TArray<FGameplayAbilitySpecHandle> ActivatedAbilitySpecHandle;
};
