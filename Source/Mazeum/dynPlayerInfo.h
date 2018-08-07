#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "playerInfo.h"
#include "dynPlayerInfo.generated.h"


USTRUCT(BlueprintType)
struct FdynPlayerInfo
{
	GENERATED_BODY()

	UPROPERTY()
		FplayerInfo save;

	UPROPERTY()
		ACharacter* playerPawn;

	FdynPlayerInfo() {

	}
};