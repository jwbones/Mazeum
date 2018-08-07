// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "serverThing.h"
#include "gameModeWithServer.generated.h"


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
};
