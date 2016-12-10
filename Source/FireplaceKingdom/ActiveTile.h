// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TileStruct.h"
/**
 * 
 */
class FIREPLACEKINGDOM_API ActiveTile
{
public:
	ActiveTile();
	~ActiveTile();

	void DeductSpawnedUnits();

	void CalculateUnitsLeftToSpawn();

	FTileStruct TileData;

	int32 UnitsLeftToSpawn;
};
