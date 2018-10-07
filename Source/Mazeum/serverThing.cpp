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

//adds a player to the list of connected players, to be called when a player connects
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


//gets the transform of a connected player's pawn by their id
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

//connects the pawn given to a dynPlayerInfo in connectedPlayers, to be used when a player connects to the server
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

//authenticates a player given their id and key
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

//returns the value in that players power slot
int32 AserverThing::getPower(int32 userId, int32 power) {
	if (!HasAuthority()) {
		return 0;
	}
	for (int32 i = 0; i < connectedPlayers.Num(); i++) {
		if (connectedPlayers[i].save.id == userId) {
			return connectedPlayers[i].save.powers[power];
		}
	}
	return 0;
}

//checks whether the player has the power
bool AserverThing::checkPower(int32 userId, int32 power) {
	if (!HasAuthority()) {
		return 0;
	}
	for (int32 i = 0; i < connectedPlayers.Num(); i++) {
		if (connectedPlayers[i].save.id == userId) {
			return connectedPlayers[i].save.powers[power] > 0;
		}
	}
	return 0;
}

//gives the specified player the specified power
int32 AserverThing::addPower(int32 userId, int32 power) {
	if (!HasAuthority()) {
		UE_LOG(LogTemp, Warning, TEXT("no authority"));
		return -2;
	}
	UE_LOG(LogTemp, Warning, TEXT("foo"));
	UE_LOG(LogTemp, Warning, TEXT("connectedPlayers.Num() = %d"), connectedPlayers.Num());
	for (int32 i = 0; i < connectedPlayers.Num(); i++) {
		UE_LOG(LogTemp, Warning, TEXT("looping, i = %d, connectedPlayers[i].save.id = %d, id to search = %d"), i, connectedPlayers[i].save.id, userId);
		if (connectedPlayers[i].save.id == userId && connectedPlayers[i].save.powers[power] == 0) {
			connectedPlayers[i].save.powers[power] = 1;
			return 0;
		}
		if (connectedPlayers[i].save.id == userId) {
			UE_LOG(LogTemp, Warning, TEXT("power int = %d"), connectedPlayers[i].save.powers[power]);
			return 2;
		}
	}
	return -5;
}

//do not use
int32 AserverThing::dummyPlayer() {
	UserverSave* serverSave = Cast<UserverSave>(UGameplayStatics::CreateSaveGameObject(UserverSave::StaticClass()));
	if (UGameplayStatics::DoesSaveGameExist(serverSave->SaveSlotName, serverSave->UserIndex)) {
		//save exists, load existing save
		serverSave = Cast<UserverSave>(UGameplayStatics::LoadGameFromSlot(serverSave->SaveSlotName, serverSave->UserIndex));
	}
	int32 userId = serverSave->playerCount;
	serverSave->playerCount++; //increment playerCount AFTER using it

	FplayerInfo newPlayer = FplayerInfo(userId, "dummy");
	serverSave->playerSaves.Add(newPlayer);
	UGameplayStatics::SaveGameToSlot(serverSave, serverSave->SaveSlotName, serverSave->UserIndex);

	addPlayer(userId);

	return userId;
}

//gets the saved return point for that userId
FVector AserverThing::getReturnPoint(int32 userId) {
	if (!HasAuthority()) {
		return { 0,0,3000 };
	}
	for (int32 i = 0; i < connectedPlayers.Num(); i++) {
		if (connectedPlayers[i].save.id == userId) {
			return connectedPlayers[i].save.returnPoint;
		}
	}
	return { 0,0,3000 };
}

//sets the return point for that userId
void AserverThing::setReturnPoint(int32 userId, FVector returnPoint) {
	if (!HasAuthority()) {
		return;
	}
	for (int32 i = 0; i < connectedPlayers.Num(); i++) {
		if (connectedPlayers[i].save.id == userId) {
			connectedPlayers[i].save.returnPoint = returnPoint;
		}
	}
}

//returns the location of a random player on the server
FVector AserverThing::getBuddy(int32 userId) {
	if (!HasAuthority()) {
		return { 0,0,0 };
	}
	int playerPos = 0;
	for (int32 i = 0; i < connectedPlayers.Num(); i++) {
		if (connectedPlayers[i].save.id == userId) {
			int playerPos = i;
		}
	}
	if (connectedPlayers.Num() == 1) { //no other players
		return connectedPlayers[playerPos].playerPawn->GetActorLocation();
	}
	int buddyPos = FMath::FRandRange(0, connectedPlayers.Num());
	while (buddyPos == playerPos) {
		buddyPos = FMath::FRandRange(0, connectedPlayers.Num());
	}
	return connectedPlayers[buddyPos].playerPawn->GetActorLocation();
}
