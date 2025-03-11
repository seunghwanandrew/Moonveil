// Genesis : The World Creation
#include "DataAssets/Input/MoonveilInputConfigDataAsset.h"

UInputAction* UMoonveilInputConfigDataAsset::FindNativeInputActionByTag(const TArray<FMoonveilInputActionConfig>& InputConfigs, const FGameplayTag& InputTag) const
{
	checkf(!InputConfigs.IsEmpty(), TEXT("Invalid Input Config Data. Maybe Array is Empty"));

	for (const FMoonveilInputActionConfig& ConfigData : InputConfigs)
	{
		if (ConfigData.InputTag == InputTag && ConfigData.InputAction)
		{
			return ConfigData.InputAction;
		}
	}

	return nullptr;
}
