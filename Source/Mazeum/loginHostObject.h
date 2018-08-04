// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineBeaconHostObject.h"
#include "loginHostObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, transient, notplaceable, config = Engine)
class MAZEUM_API AloginHostObject : public AOnlineBeaconHostObject
{
	GENERATED_BODY()
	
	virtual AOnlineBeaconClient* SpawnBeaconActor(class UNetConnection* clientConnection) override;
	virtual void OnClientConnected(class AOnlineBeaconClient* newClient, class UNetConnection* clientConnection) override;
	
	virtual bool init();

	AloginHostObject(const FObjectInitializer& ObjectInitializer);


	
	
};
