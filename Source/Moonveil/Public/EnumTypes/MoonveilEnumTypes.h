// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class FMoonveilAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

UENUM(BlueprintType)
enum class EConfirmType : uint8
{
	Yes,
	No
};

UENUM(BlueprintType)
enum class EValidType : uint8
{
	Valid,
	InValid
};

UENUM(BlueprintType)
enum class ESuccessType : uint8
{
	Success,
	Fail
};