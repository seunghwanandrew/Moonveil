// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "Components/MoonveilPawnExtensionComponent.h"
#include "GameplayTagContainer.h"
#include "MoonveilBaseCombatComponent.generated.h"

class AMoonveilBaseWeapon;

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand,
};

UCLASS()
class MOONVEIL_API UMoonveilBaseCombatComponent : public UMoonveilPawnExtensionComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Combat|Weapon")
	void RegisterSpawnedWeapon(AMoonveilBaseWeapon* WeaponToRegister, const FGameplayTag& WeaponTagToRegister, bool bShouldbeEquippedAsCurrentWeapon);

protected:
	UFUNCTION(BlueprintCallable, Category = "Combat|Weapon")
	AMoonveilBaseWeapon* FindCharacterCarriedWeaponByTag(FGameplayTag WeaponTagToFind) const;
	UFUNCTION(BlueprintCallable, Category = "Combat|Weapon")
	AMoonveilBaseWeapon* GetCharacterCurrentEquippedWeapon() const;
	UFUNCTION(BlueprintCallable, Category = "Combat|Weapon")
	void ToggleWeaponCollision(bool bWeaponCollisionEnable, EDamageType DamageType = EDamageType::CurrentEquippedWeapon);

	virtual void TargetOnWeapon(AActor* Target);
	virtual void TargetOffWeapon(AActor* Target);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat|Weapon")
	FGameplayTag CurrentEquippedWeaponTag;

	TMap<FGameplayTag, AMoonveilBaseWeapon*> CharacterCarriedWeapons;
	TArray<AActor*> OverlappedTargetArray;
};
