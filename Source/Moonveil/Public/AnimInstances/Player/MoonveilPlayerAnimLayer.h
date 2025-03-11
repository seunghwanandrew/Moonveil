// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/MoonveilBaseAnimInstance.h"
#include "MoonveilPlayerAnimLayer.generated.h"

class UMoonveilCharacterAnimInstance;

UCLASS()
class MOONVEIL_API UMoonveilPlayerAnimLayer : public UMoonveilBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UMoonveilCharacterAnimInstance* GetPlayerAnimInstance() const;
};
