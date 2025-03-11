// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/MoonveilInputConfigDataAsset.h"
#include "GamePlayTags/MoonveilGameplayTags.h"
#include "MoonveilEnhancedInputComponent.generated.h"

UCLASS()
class MOONVEIL_API UMoonveilEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserObject, class CallbackFunc>
	void BindNativeInputAction(const UMoonveilInputConfigDataAsset* InputActionDataConfig, const FGameplayTag& InputActionTag, ETriggerEvent TriggerEvent, UserObject* ObjectContext, CallbackFunc Func);
	template<class UserObject, class CallbackFunc>
	void BindAbilityInputAction(const UMoonveilInputConfigDataAsset* InputActionDataConfig, UserObject* ObjectContext, CallbackFunc OnPressedFunc, CallbackFunc OnReleasedFunc);
};

template<class UserObject, class CallbackFunc>
inline void UMoonveilEnhancedInputComponent::BindNativeInputAction(const UMoonveilInputConfigDataAsset* InputActionDataConfig, const FGameplayTag& InputActionTag, ETriggerEvent TriggerEvent, UserObject* ObjectContext, CallbackFunc Func)
{
	UInputAction* InputAction = InputActionDataConfig->FindNativeInputActionByTag(InputActionDataConfig->NativeInputActionConfig, InputActionTag);

	if (InputAction)
	{
		BindAction(InputAction, TriggerEvent, ObjectContext, Func);
	}
}

template<class UserObject, class CallbackFunc>
inline void UMoonveilEnhancedInputComponent::BindAbilityInputAction(const UMoonveilInputConfigDataAsset* InputActionDataConfig, UserObject* ObjectContext, CallbackFunc OnPressedFunc, CallbackFunc OnReleasedFunc)
{
	for (const FMoonveilInputActionConfig& AbilityInput : InputActionDataConfig->AbilityInputActionConfig)
	{
		if (!AbilityInput.IsValid()) continue;

		BindAction(AbilityInput.InputAction, ETriggerEvent::Started, ObjectContext, OnPressedFunc, AbilityInput.InputTag);
		BindAction(AbilityInput.InputAction, ETriggerEvent::Completed, ObjectContext, OnReleasedFunc, AbilityInput.InputTag);
	}
}