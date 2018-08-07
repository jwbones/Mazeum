// Fill out your copyright notice in the Description page of Project Settings.

#include "clientSave.h"
#include "Mazeum.h"

UclientSave::UclientSave()
{
	SaveSlotName = TEXT("user");
	UserIndex = 0;
	userId = -1;
	userKey = TEXT("bad");
}

