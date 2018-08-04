// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineBeaconHost.h"
#include "loginHost.generated.h"

class AOnlineBeaconHostObject;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, transient, notplaceable, config = Engine)
class MAZEUM_API AloginHost : public AOnlineBeaconHost
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "loginHost")
	bool startHost();

	UFUNCTION(BlueprintCallable, Category = "loginHost")
	void addHost(AOnlineBeaconHostObject* hostObject);

	AloginHost(const FObjectInitializer& ObjectInitializer);
	
protected:
	bool ready;
};
