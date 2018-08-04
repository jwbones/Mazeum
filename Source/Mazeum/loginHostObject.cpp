// Fill out your copyright notice in the Description page of Project Settings.

#include "loginHostObject.h"
#include "myClient.h"

AloginHostObject::AloginHostObject(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	//specify the beacon to use
	ClientBeaconActorClass = AmyClient::StaticClass();
	BeaconTypeName = ClientBeaconActorClass->GetName();

}

bool AloginHostObject::init() {
	return true;
}

void AloginHostObject::OnClientConnected(AOnlineBeaconClient* newClient, UNetConnection* clientConnection) {
	Super::OnClientConnected(newClient, clientConnection);

	AmyClient* loginClient = Cast<AmyClient>(newClient);
	if (loginClient != NULL)
	{
		loginClient->ClientStart();
	}
}

AOnlineBeaconClient* AloginHostObject::SpawnBeaconActor(UNetConnection* ClientConnection)
{
	//Just super for now, technically you can return NULL here as well to prevent spawning
	return Super::SpawnBeaconActor(ClientConnection);
}
