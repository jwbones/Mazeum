// Fill out your copyright notice in the Description page of Project Settings.

#include "myClient.h"
#include "Kismet/GameplayStatics.h"
#include "clientSave.h"
#include "serverSave.h"
#include "Engine/World.h"
#include "Runtime/Core/Public/Misc/ConfigCacheIni.h"




bool AmyClient::ServerSetup_Validate() {
	return true;
}

/* Creates a userid/key pair and create a save for the new
player
*/
void AmyClient::ServerSetup_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("serverSetup called"));
	int32 userId;
	UserverSave* serverSave = Cast<UserverSave>(UGameplayStatics::CreateSaveGameObject(UserverSave::StaticClass()));
	if (UGameplayStatics::DoesSaveGameExist(serverSave->SaveSlotName, serverSave->UserIndex)) {
		//save exists, load existing save
		serverSave = Cast<UserverSave>(UGameplayStatics::LoadGameFromSlot(serverSave->SaveSlotName, serverSave->UserIndex));
	}
	userId = serverSave->playerCount;
	serverSave->playerCount++; //increment playerCount AFTER using it
	
	//building key
	char buildKey[21];
	for (int i = 0; i < 20; i++) {
		buildKey[i] = FMath::RandRange(65, 90);
	}
	buildKey[20] = 0;
	//end building key

	FString userKey = FString(ANSI_TO_TCHAR(buildKey)); //add the key at userId in playerKeys
	FplayerInfo newPlayer = FplayerInfo(userId, userKey);
	serverSave->playerSaves.Add(newPlayer);
	UGameplayStatics::SaveGameToSlot(serverSave, serverSave->SaveSlotName, serverSave->UserIndex);

	ClientSetup(userId, userKey);

}

bool AmyClient::ServerLogin_Validate(int32 userId, const FString& userKey) {
	UE_LOG(LogTemp, Warning, TEXT("serverLogin called"));
	//load the server saves
	UserverSave* serverSave = Cast<UserverSave>(UGameplayStatics::CreateSaveGameObject(UserverSave::StaticClass()));
	serverSave = Cast<UserverSave>(UGameplayStatics::LoadGameFromSlot(serverSave->SaveSlotName, serverSave->UserIndex));
	if (!serverSave->playerSaves.IsValidIndex(userId)) {
		//bad id
		UE_LOG(LogTemp, Warning, TEXT("bad ID"));
		return false;
	}
	//make sure player num is resonable
	FplayerInfo saveToCheck = serverSave->playerSaves[userId];

	//check keys
	if (!userKey.Equals(saveToCheck.key)) {
		//wrong key
		UE_LOG(LogTemp, Warning, TEXT("Key mismatch"));
		return false;
	}

	//all good
	UE_LOG(LogTemp, Warning, TEXT("serverLogin passed auth"));
	return true;
}



void AmyClient::ServerLogin_Implementation(int32 userId, const FString& userKey) {
	UE_LOG(LogTemp, Warning, TEXT("serverLogin implementation called"));
	//login time
	AgameModeWithServer* gameModeRef = (AgameModeWithServer*)GetWorld()->GetAuthGameMode();
	AserverThing* serverRef = gameModeRef->getServer();
	serverRef->addPlayer(userId);
	ClientLogin();
}

void AmyClient::ClientLogin_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("clientLogin called"));
	APlayerController * player = GetWorld()->GetFirstPlayerController();
	FString serverIp;
	GConfig->GetString(TEXT("/Script/OnlineSubsystemUtils.OnlineBeaconHost"), TEXT("ServerIp"), serverIp, GEngineIni);
	FString port;
	GConfig->GetString(TEXT("/Script/OnlineSubsystemUtils.OnlineBeaconHost"), TEXT("ServerPort"), port, GEngineIni);
	serverIp += ":";
	serverIp += port;
	player->ClientTravel(serverIp, TRAVEL_Absolute);
}


bool AmyClient::connectToServer() {
	UE_LOG(LogTemp, Warning, TEXT("trying to connect"));
	//connect to the server
	FString serverIp;
	GConfig->GetString(TEXT("/Script/OnlineSubsystemUtils.OnlineBeaconHost"), TEXT("ServerIp"), serverIp, GEngineIni);
	FURL url(NULL, *serverIp, ETravelType::TRAVEL_Absolute);

	int32 portToUse;
	GConfig->GetInt(TEXT("/Script/OnlineSubsystemUtils.OnlineBeaconHost"), TEXT("ListenPort"), portToUse, GEngineIni);
	url.Port = portToUse;

	return InitClient(url);
}

void AmyClient::ClientStart_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("trying to start"));
	//check if the client has a save
	if (!UGameplayStatics::DoesSaveGameExist("user", 0)) {
		//no save, make one
		ServerSetup();
	}
	if (!UGameplayStatics::DoesSaveGameExist("user", 0)) {
		//still no save
		UE_LOG(LogTemp, Warning, TEXT("Failed first setup"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("created save"));

	UclientSave* clientSave = Cast<UclientSave>(UGameplayStatics::CreateSaveGameObject(UclientSave::StaticClass()));
	clientSave = Cast<UclientSave>(UGameplayStatics::LoadGameFromSlot(clientSave->SaveSlotName, clientSave->UserIndex));
	UE_LOG(LogTemp, Warning, TEXT("trying to connect to server"));
	ServerLogin(clientSave->userId, clientSave->userKey);


}

void AmyClient::ClientSetup_Implementation(int32 userId, const FString& userKey) {
	UE_LOG(LogTemp, Warning, TEXT("clientSetup called"));
	UclientSave* localSave = Cast<UclientSave>(UGameplayStatics::CreateSaveGameObject(UclientSave::StaticClass()));
	localSave->userId = userId;
	localSave->userKey = userKey;
	UGameplayStatics::SaveGameToSlot(localSave, localSave->SaveSlotName, localSave->UserIndex);

}
