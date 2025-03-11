// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoonveilBaseWeapon.generated.h"

DECLARE_DELEGATE_OneParam(FWeaponInteractionDelegate, AActor* Actor);

UCLASS()
class MOONVEIL_API AMoonveilBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
#pragma region DelegateDef
	FWeaponInteractionDelegate WeaponTargetOn;
	FWeaponInteractionDelegate WeaponTargetOff;
#pragma endregion

#pragma region Getter
	FORCEINLINE class UBoxComponent* GetWeaponCollisionBox() { return WeaponCollisionBox; }
#pragma endregion
	AMoonveilBaseWeapon();
	UFUNCTION(Category = "Moonveil|Delegate")
	virtual void OnWeaponCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(Category = "Moonveil|Delegate")
	virtual void OnWeaponCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Weapon")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Weapon")
	class UBoxComponent* WeaponCollisionBox;
};
