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

	UPROPERTY(VisibleAnywhere)
		int32 powers[8] = { 0 };


	FplayerInfo() {
		//TODO set savedLocation to the spawn location
	}

	FplayerInfo(int32 idToUse, FString keyToUse) {
		id = idToUse;
		key = keyToUse;
		savedLocation = FTransform(FVector(-200.0, 100.0, 500.0));
		//TODO set savedLocation to the spawn location NOT LIKE AN APE
	}

};
