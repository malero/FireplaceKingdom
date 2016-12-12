// Fill out your copyright notice in the Description page of Project Settings.

#include "FireplaceKingdom.h"
#include "QueuedTile.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

void UQueuedTile::DeductSpawnedUnits()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString("Deducting"));
	UnitsLeftToSpawn -= UnitsPerSpawn;
}

void UQueuedTile::DeductSpawnedUnit()
{
	UnitsLeftToSpawn -= 1;
}

void UQueuedTile::SetTileData(FTileStruct *Data)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString("Setting Tile Data: ") + FString(Data->Name.ToString()) + FString::FromInt(Data->UnitsPerSpawn));
	TileData = Data;
	Name = Data->Name;
	Unit = Data->Unit;
	UnitsToSpawn = Data->UnitsToSpawn;
	UnitsPerSpawn = Data->UnitsPerSpawn;
	SpawnDelay = Data->SpawnDelay;
	UnitsLeftToSpawn = UnitsToSpawn;

	Health = Data->Health;
	AttackMin = Data->AttackMin;
	AttackMax = Data->AttackMax;
	AttackDistance = Data->AttackDistance;
	VisionDistance = Data->VisionDistance;
	MovementSpeed = Data->MovementSpeed;
}

int32 UQueuedTile::GetUnitsLeftToSpawn()
{
	return UnitsLeftToSpawn;
}
