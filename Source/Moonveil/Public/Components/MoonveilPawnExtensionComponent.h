// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoonveilPawnExtensionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOONVEIL_API UMoonveilPawnExtensionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	template<class T>
	T* GetOwningPawn() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "'T' Template Parameter must be derived from APawn.");
		return Cast<T>(GetOwner());
	}
	
	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}

	template<class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "'T' Template Parameter must be derived from AController");
		return Cast<T>(GetOwningPawn()->GetController());
	}
};
