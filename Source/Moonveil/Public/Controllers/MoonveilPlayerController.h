// Genesis : The World Creation
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "MoonveilPlayerController.generated.h"

UCLASS()
class MOONVEIL_API AMoonveilPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
#pragma region Getter
	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const override { return PlayerGenericTeamId; }
#pragma endregion
	AMoonveilPlayerController();

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGenericTeamId PlayerGenericTeamId;
};
