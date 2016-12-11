// Fill out your copyright notice in the Description page of Project Settings.

#include "FireplaceKingdom.h"
#include "QueuedTile.h"

void UQueuedTile::CalculateUnitsLeftToSpawn()
{
	UnitsLeftToSpawn = TileData.UnitsToSpawn;
}

void UQueuedTile::DeductSpawnedUnits()
{
	UnitsLeftToSpawn -= TileData.UnitsPerSpawn;
}
