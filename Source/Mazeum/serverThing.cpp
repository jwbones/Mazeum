// Fill out your copyright notice in the Description page of Project Settings.

#include "serverThing.h"



// Sets default values
AserverThing::AserverThing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AserverThing::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AserverThing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AserverThing::addPlayer(int32 userId) {
	//load the saved info
	UserverSave* serverSave = Cast<UserverSave>(UGameplayStatics::CreateSaveGameObject(UserverSave::StaticClass()));
	serverSave = Cast<UserverSave>(UGameplayStatics::LoadGameFromSlot(serverSave->SaveSlotName, serverSave->UserIndex));
}

