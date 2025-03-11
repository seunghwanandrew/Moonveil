// Genesis : The World Creation
#include "AbilitySystem/MoonveilAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "FunctionLibrary/MoonveilFunctionLibrary.h"
#include "GamePlayTags/MoonveilGameplayTags.h"
#include "Interfaces/MoonveilPawnUIInterface.h"
#include "Components/UI/MoonveilPawnUIComponent.h"
#include "Components/UI/MoonveilPlayerUIComponent.h"

#include "MoonveilDebugHelpers.h"

UMoonveilAttributeSet::UMoonveilAttributeSet()
{
	InitCurrentHealth(1.0f);
	InitMaxHealth(1.0f);
	InitCurrentRage(1.0f);
	InitMaxRage(1.0f);
	InitAttackPower(1.0f);
	InitDefensePower(1.0f);
}

void UMoonveilAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (!PawnUIInterfaceRef.IsValid())
	{
		if (Data.Target.GetAvatarActor()->Implements<UMoonveilPawnUIInterface>())
		{
			PawnUIInterfaceRef = TWeakInterfacePtr<IMoonveilPawnUIInterface>(Data.Target.GetAvatarActor());
		}
	}

	UMoonveilPawnUIComponent* PawnUIComponent = PawnUIInterfaceRef.IsValid() ? PawnUIInterfaceRef->GetPawnUIComponent() : nullptr;

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float PostValueOfHealth = FMath::Clamp(GetCurrentHealth(), 0.0f, GetMaxHealth());

		SetCurrentHealth(PostValueOfHealth);

		if (PawnUIComponent)
		{
			PawnUIComponent->OnCurrentHealthPercentChanged.Broadcast(GetCurrentHealth()/GetMaxHealth());
		}
	}

	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float PostValueOfRage = FMath::Clamp(GetCurrentRage(), 0.0f, GetMaxRage());

		SetCurrentRage(PostValueOfRage);

		UMoonveilPlayerUIComponent* PlayerUIComponent = PawnUIInterfaceRef.IsValid() ? PawnUIInterfaceRef->GetPlayerUIComponent() : nullptr;
		if (PlayerUIComponent)
		{
			PlayerUIComponent->OnCurrentRagePercentChanged.Broadcast(GetCurrentRage() / GetMaxRage());
		}
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float PreValueOfHealth = GetCurrentHealth();
		const float DamageAmount = GetDamageTaken();

		const float PostValueOfHealth = FMath::Clamp(PreValueOfHealth - DamageAmount, 0.0f, GetMaxHealth());

		SetCurrentHealth(PostValueOfHealth);

		if (bDebugMode)
		{
			const FString Msg = FString::Printf(TEXT("PreValue Of Health : %f, Damage Amount : %f, PostValue Of Health : %f"), PreValueOfHealth, DamageAmount, PostValueOfHealth);
			Debug::Print(Msg, FColor::Emerald);
		}

		// TODO : Notify UI
		if (PawnUIComponent)
		{
			PawnUIComponent->OnCurrentHealthPercentChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
		}
		
		// TODO : Handle Death
		if (GetCurrentHealth() <= 0.0f)
		{
			UMoonveilFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), FMoonveilGameplayTags::Event_Status_Death);
		}
	}
}
