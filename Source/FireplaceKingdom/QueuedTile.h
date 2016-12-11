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
	void DeductSpawnedUnits();

	void CalculateUnitsLeftToSpawn();

	FTileStruct TileData;

	int32 UnitsLeftToSpawn;
	
};
