// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoonveilUserWidgetBase.generated.h"

class UMoonveilPlayerUIComponent;
class UMoonveilEnemyUIComponent;

UCLASS()
class MOONVEIL_API UMoonveilUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreatedWidget(AActor* OwningEnemyActor);

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Listen Player UI Component Broadcast"))
	void BP_OnListenPlayerUIComponentBroadcast(UMoonveilPlayerUIComponent* OwningPlayerUIComponent);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Listen Enemy UI Component Broadcast"))
	void BP_OnListenEnemyUIComponentBroadcast(UMoonveilEnemyUIComponent* OwningEnemyUIComponent);
};
