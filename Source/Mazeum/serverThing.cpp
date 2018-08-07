// Fill out your copyright notice in the Description page of Project Settings.
//test
#include "serverThing.h"


// Sets default values
AserverThing::AserverThing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bNetLoadOnClient = false;
	bReplicates = false;
	UserverSave* serverSave = Cast<UserverSave>(UGameplayStatics::CreateSaveGameObject(UserverSave::StaticClass()));
	if (!UGameplayStatics::DoesSaveGameExist(serverSave->SaveSlotName, serverSave->UserIndex)) {
		UGameplayStatics::SaveGameToSlot(serverSave, serverSave->SaveSlotName, serverSave->UserIndex);
	}

}


void AserverThing::addPlayer(int32 userId) {
	if (!HasAuthority()) {
		return;
	}
	//load the saved info
	UserverSave* serverSave = Cast<UserverSave>(UGameplayStatics::CreateSaveGameObject(UserverSave::StaticClass()));
	serverSave = Cast<UserverSave>(UGameplayStatics::LoadGameFromSlot(serverSave->SaveSlotName, serverSave->UserIndex));
	FdynPlayerInfo newPlayer = FdynPlayerInfo();
	newPlayer.save = serverSave->playerSaves[userId];
	connectedPlayers.Add(newPlayer);
}



//search for the connected player with the specified user id and update the playerInfo associated with it
void AserverThing::updatePlayerById(int32 userId) {
	if (!HasAuthority()) {
		return;
	}
	for (int32 i = 0; i < connectedPlayers.Num(); i++) {
		if (connectedPlayers[i].save.id == userId) {
			connectedPlayers[i].save.savedLocation = connectedPlayers[i].playerPawn->GetTransform();
		}
	}
}



//update the playerInfo for all players
void AserverThing::updatePlayerAll() {
	if (!HasAuthority()) {
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("updating players"));
	for (int32 i = 0; i < connectedPlayers.Num(); i++) {
		if (IsValid(connectedPlayers[i].playerPawn)) {
			connectedPlayers[i].save.savedLocation = connectedPlayers[i].playerPawn->GetTransform();
			UE_LOG(LogTemp, Warning, TEXT("player updated, userId = %d"), connectedPlayers[i].save.id);
		}
	}
}



//saves all the playerInfos to disk
void AserverThing::savePlayers() {
	if (!HasAuthority()) {
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("saving to disk"));
	UserverSave* serverSave = Cast<UserverSave>(UGameplayStatics::CreateSaveGameObject(UserverSave::StaticClass()));
	serverSave = Cast<UserverSave>(UGameplayStatics::LoadGameFromSlot(serverSave->SaveSlotName, serverSave->UserIndex));
	for (int32 i = 0; i < connectedPlayers.Num(); i++) {
		int32 userId = connectedPlayers[i].save.id;
		serverSave->playerSaves[userId] = connectedPlayers[i].save;
	}
	UGameplayStatics::SaveGameToSlot(serverSave, serverSave->SaveSlotName, serverSave->UserIndex);
	UE_LOG(LogTemp, Warning, TEXT("saved to disk"));
	//perform cleanup on disconnected players
	for (int32 i = 0; i < connectedPlayers.Num(); i++) {
		if (!IsValid(connectedPlayers[i].playerPawn)) {
			UE_LOG(LogTemp, Warning, TEXT("player removed, userId = %d"), connectedPlayers[i].save.id);
			connectedPlayers.RemoveAt(i);
			i--;
		}
	}
}



FTransform AserverThing::getTransformById(int32 userId) {
	if (!HasAuthority()) {
		return FTransform();
	}
	for (int32 i = 0; i < connectedPlayers.Num(); i++) {
		if (connectedPlayers[i].save.id == userId) {
			return connectedPlayers[i].save.savedLocation;
		}
	}
	return FTransform();
}

void AserverThing::bindPawn(int32 userId, ACharacter* pawn) {
	if (!HasAuthority()) {
		return;
	}
	for (int32 i = 0; i < connectedPlayers.Num(); i++) {
		if (connectedPlayers[i].save.id == userId) {
			connectedPlayers[i].playerPawn = pawn;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("player bound, userId = %d"), userId);
}


bool AserverThing::authenticatePair(int32 userId, const FString& keyToCheck) {
	UE_LOG(LogTemp, Warning, TEXT("authenticatePair called"));
	if (!HasAuthority()) {
		return false;
	}
	for (int32 i = 0; i < connectedPlayers.Num(); i++) {
		if (connectedPlayers[i].save.id == userId) {
			if (connectedPlayers[i].save.key.Equals(keyToCheck)) {
				UE_LOG(LogTemp, Warning, TEXT("good key serverThing"));
				return true;
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("bad key serverThing"));
				return false;				
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("not found"));
	return false;
}