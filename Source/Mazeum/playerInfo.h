#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "playerInfo.generated.h"
USTRUCT(BlueprintType)
struct FplayerInfo
{
	GENERATED_BODY()
		
		UPROPERTY()
		int32 id;

		UPROPERTY()
		FString key;

	UPROPERTY(VisibleAnywhere)
		FTransform savedLocation;

	FplayerInfo() {
		//TODO set savedLocation to the spawn location
	}

	FplayerInfo(int32 idToUse, FString keyToUse) {
		id = idToUse;
		key = keyToUse;
		//TODO set savedLocation to the spawn location
	}

};
