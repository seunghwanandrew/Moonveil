// Genesis : The World Creation
#include "UI/Widgets/MoonveilUserWidgetBase.h"
#include "Interfaces/MoonveilPawnUIInterface.h"

void UMoonveilUserWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	IMoonveilPawnUIInterface* PawnUIInterface = nullptr;
	if (OwningEnemyActor->Implements<UMoonveilPawnUIInterface>())
	{
		PawnUIInterface = Cast<IMoonveilPawnUIInterface>(OwningEnemyActor);
	}

	if (PawnUIInterface)
	{
		if (UMoonveilEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent())
		{
			BP_OnListenEnemyUIComponentBroadcast(EnemyUIComponent);
		}
	}
}

void UMoonveilUserWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	IMoonveilPawnUIInterface* PawnUIInterface = nullptr;
	if (GetOwningPlayerPawn()->Implements<UMoonveilPawnUIInterface>())
	{
		PawnUIInterface = Cast<IMoonveilPawnUIInterface>(GetOwningPlayerPawn());
	}

	if (PawnUIInterface)
	{
		if (UMoonveilPlayerUIComponent* PlayerUIComponent = PawnUIInterface->GetPlayerUIComponent())
		{
			BP_OnListenPlayerUIComponentBroadcast(PlayerUIComponent);
		}
	}
}
