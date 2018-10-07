// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "playerInfo.h"
#include "Kismet/KismetMathLibrary.h"
#include "serverSave.generated.h"


/**
 * 
 */
UCLASS()
class MAZEUM_API UserverSave : public USaveGame
{
	GENERATED_BODY()

	public:

		UPROPERTY(VisibleAnywhere, Category = Basic)
		int32 playerCount;
		
		UPROPERTY(VisibleAnywhere, Category = Basic)
		TArray<FplayerInfo> playerSaves;

		UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

		UPROPERTY(VisibleAnywhere, Category = Basic)
		int32 UserIndex;

		UserverSave();
	
};

