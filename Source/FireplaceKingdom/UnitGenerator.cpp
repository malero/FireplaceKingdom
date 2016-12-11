// Fill out your copyright notice in the Description page of Project Settings.

#include "FireplaceKingdom.h"
#include "UnitGenerator.h"
#include "ActiveTile.h"
#include "TileStruct.h"
#include "Engine/DataTable.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>


// Sets default values
AUnitGenerator::AUnitGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnTimer = SpawnDelay;

}

// Called when the game starts or when spawned
void AUnitGenerator::BeginPlay()
{
	Super::BeginPlay();
	SpawnTimer = 0;
	// Make UTileComponents from DebugTiles(if any are present)
	for (int i = 0; i < DebugTiles.Num(); i++) {
		AddTile(DebugTiles[i]);
	}
}

void AUnitGenerator::AddTile(FName ID)
{

	FTileStruct Row = *DataTable->FindRow<FTileStruct>(ID, TEXT(""));
	ActiveTile _Tile;
	_Tile.TileData = Row;
	_Tile.CalculateUnitsLeftToSpawn();
	Tiles.Add(_Tile);
}

// Called every frame
void AUnitGenerator::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	SpawnTimer -= DeltaTime;
	if (SpawnTimer <= 0) {
		if (Tiles.Num() > 0 && pTile == NULL) {
			Tile = Tiles.Pop();
			pTile = &Tile;
			SetSpawnTimer();
		} else if(pTile != NULL) {
			SetSpawnTimer();
			GenerateUnit();
		} else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("No units left to spawn"));
		}
	}
}

void AUnitGenerator::GenerateUnit()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Spawning"));
	UWorld* const World = GetWorld(); // get a reference to the world
	if (World) {
		// if world exists
		AUnit* Unit = World->SpawnActor<AUnit>(Tile.TileData.Unit, GetActorLocation(), GetActorRotation());
		Unit->Lane = Lane;
		Unit->SetActorLocation(GetActorLocation());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Pre: " + FString::FromInt(Tile.UnitsLeftToSpawn));
		Tile.DeductSpawnedUnits();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Post: " + FString::FromInt(Tile.UnitsLeftToSpawn));
		if (Tile.UnitsLeftToSpawn <= 0) {
			pTile = NULL;
		}
	}
}

void AUnitGenerator::SetSpawnTimer()
{
	if (pTile != NULL) {
		SpawnTimer = Tile.TileData.SpawnDelay;
	}
}
