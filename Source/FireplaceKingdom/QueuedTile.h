// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "TileStruct.h"
#include "QueuedTile.generated.h"

/**
 * 
 */
UCLASS()
class FIREPLACEKINGDOM_API UQueuedTile : public UObject
{
	GENERATED_BODY()

public:
	int32 GetUnitsLeftToSpawn();
	void DeductSpawnedUnits();
	void DeductSpawnedUnit();

	FName Name;

	TSubclassOf<AUnit> Unit;

	int32 UnitsToSpawn;

	int32 UnitsPerSpawn;

	float Health;
	float AttackMin;
	float AttackMax;
	float AttackDistance;
	float VisionDistance; // How far can this unit see and spot enemeies/other PoIs?
	float MovementSpeed;

	float SpawnDelay;
	
	void SetTileData(FTileStruct *Data);

protected:
	int32 UnitsLeftToSpawn;
	FTileStruct* TileData;
};
