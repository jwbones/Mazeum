// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "clientSave.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MAZEUM_API UclientSave : public USaveGame
{
	GENERATED_BODY()

	public:

		UPROPERTY(VisibleAnywhere, Category = Basic, BlueprintReadWrite)
		int32 userId;

		UPROPERTY(VisibleAnywhere, Category = Basic)
		FString userKey;

		UPROPERTY(VisibleAnywhere, Category = Basic, BlueprintReadWrite)
		FString SaveSlotName;

		UPROPERTY(VisibleAnywhere, Category = Basic, BlueprintReadWrite)
		int32 UserIndex;

		UclientSave();

};
