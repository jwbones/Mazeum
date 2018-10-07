// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "serverThing.h"
#include "gameModeWithServer.generated.h"

#define HOME_POINT_TESTPLANE (100.0, 100.0, 300.0)

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MAZEUM_API AgameModeWithServer : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	AserverThing* server;

public:
	UFUNCTION()
	AserverThing* getServer();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FVector homePoint = FVector(HOME_POINT_TESTPLANE);
};
