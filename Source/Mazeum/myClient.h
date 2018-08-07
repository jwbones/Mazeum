// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineBeaconClient.h"
#include "gameModeWithServer.h"
#include "myClient.generated.h"

#define SERVER_IP "108.216.158.79"


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, transient, notplaceable, config = Engine)
class MAZEUM_API AmyClient : public AOnlineBeaconClient
{
	GENERATED_BODY()



	//perform first-time setup on client
	UFUNCTION(Client, Reliable)
	virtual void ClientSetup(int32 userId, const FString& userKey);
	virtual void ClientSetup_Implementation(int32 userId, const FString& userKey);

	//login for client
	UFUNCTION(Client, Reliable)
	virtual void ClientLogin();
	virtual void ClientLogin_Implementation();

	//perform first-time setup on server
	UFUNCTION(Server, reliable, WithValidation)
	virtual void ServerSetup();
	virtual void ServerSetup_Implementation();
	virtual bool ServerSetup_Validate();

	//login for server
	UFUNCTION(Server, reliable, WithValidation)
	virtual void ServerLogin(int32 userId, const FString& userKey);
	virtual void ServerLogin_Implementation(int32 userId, const FString& userKey);
	virtual bool ServerLogin_Validate(int32 userId, const FString& userKey);
	
public:
	//login for client
	UFUNCTION(Client, Reliable, BlueprintCallable)
	virtual void ClientStart();
	virtual void ClientStart_Implementation();

	UFUNCTION(BlueprintCallable)
	virtual bool connectToServer();
};
