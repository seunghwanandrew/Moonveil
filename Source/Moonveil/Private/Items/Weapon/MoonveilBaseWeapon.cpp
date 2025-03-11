// Genesis : The World Creation
#include "Items/Weapon/MoonveilBaseWeapon.h"
#include "Components/BoxComponent.h"
#include "FunctionLibrary/MoonveilFunctionLibrary.h"

#include "MoonveilDebugHelpers.h"

AMoonveilBaseWeapon::AMoonveilBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollsionBox"));
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetBoxExtent(FVector(20.0f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMoonveilBaseWeapon::OnWeaponCollisionBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &AMoonveilBaseWeapon::OnWeaponCollisionEndOverlap);
}

void AMoonveilBaseWeapon::OnWeaponCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* OwningPawn = GetInstigator();
	APawn* Target = Cast<APawn>(OtherActor);
	
	if (!OwningPawn || !Target) return;

	if (UMoonveilFunctionLibrary::IsTargetPawnHostile(OwningPawn, Target))
	{
		WeaponTargetOn.ExecuteIfBound(OtherActor);
	}
}

void AMoonveilBaseWeapon::OnWeaponCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* OwningPawn = GetInstigator();
	APawn* Target = Cast<APawn>(OtherActor);

	if (!OwningPawn || !Target) return;

	if (UMoonveilFunctionLibrary::IsTargetPawnHostile(OwningPawn, Target))
	{
		WeaponTargetOff.ExecuteIfBound(OtherActor);
	}
}
