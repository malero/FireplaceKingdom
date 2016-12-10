// Fill out your copyright notice in the Description page of Project Settings.

#include "FireplaceKingdom.h"
#include "ActiveTile.h"

ActiveTile::ActiveTile()
{
}

ActiveTile::~ActiveTile()
{
}

void ActiveTile::CalculateUnitsLeftToSpawn()
{
	UnitsLeftToSpawn = TileData.UnitsPerSpawn * TileData.UnitsToSpawn;
}

void ActiveTile::DeductSpawnedUnits()
{
	UnitsLeftToSpawn -= TileData.UnitsPerSpawn;
}