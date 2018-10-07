// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "playerInfo.h"
#include "Kismet/GameplayStatics.h"
#include "serverSave.h"
#include "dynPlayerInfo.h"
#include "GameFramework/Character.h"
#include "serverThing.generated.h"


UCLASS(BlueprintType)
class MAZEUM_API AserverThing : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AserverThing();

	UFUNCTION(BlueprintCallable)
	virtual void addPlayer(int32 userId);
	
	UFUNCTION(BlueprintCallable)
	virtual void updatePlayerById(int32 userId);

	UFUNCTION(BlueprintCallable)
	virtual void updatePlayerAll();

	UFUNCTION(BlueprintCallable)
	virtual void savePlayers();

	UFUNCTION(BlueprintCallable)
	virtual FTransform getTransformById(int32 userId);

	UFUNCTION(BlueprintCallable)
	virtual int32 getPower(int32 userId, int32 power);
	
	UFUNCTION(BlueprintCallable)
	virtual int32 addPower(int32 userId, int32 power);

	UFUNCTION(BlueprintCallable)
	virtual void bindPawn(int32 userId, ACharacter* pawn);

	UFUNCTION(BlueprintCallable)
	virtual bool authenticatePair(int32 userId, const FString& keyToCheck);

	UFUNCTION(BlueprintCallable)
	virtual bool checkPower(int32 userId, int32 power);

	UFUNCTION(BlueprintCallable)
	virtual FVector getReturnPoint(int32 userId);

	UFUNCTION(BlueprintCallable)
	virtual void setReturnPoint(int32 userId, FVector returnPoint);

	UFUNCTION(BlueprintCallable)
	virtual FVector getBuddy(int32 userId);

	//dev only
	UFUNCTION(BlueprintCallable)
	virtual int32 dummyPlayer();



private:
	UPROPERTY()
	TArray<FdynPlayerInfo> connectedPlayers;	
	
};
