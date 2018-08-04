// Fill out your copyright notice in the Description page of Project Settings.

#include "loginHost.h"
#include "OnlineBeaconHostObject.h"

AloginHost::AloginHost(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	//Set the beacon host state to allow requests
	BeaconState = EBeaconState::AllowRequests;
}

bool AloginHost::startHost() {
	ready = InitHost();
	return ready;
}

void AloginHost::addHost(AOnlineBeaconHostObject* hostObject) {
	if (ready)
	{
		RegisterHost(hostObject);
	}
}