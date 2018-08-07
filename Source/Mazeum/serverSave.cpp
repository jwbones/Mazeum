// Fill out your copyright notice in the Description page of Project Settings.

#include "serverSave.h"
#include "Mazeum.h"

UserverSave::UserverSave()
{
	SaveSlotName = TEXT("server");
	UserIndex = 0;
	playerCount = 0;
	playerSaves = TArray<FplayerInfo>();
}



