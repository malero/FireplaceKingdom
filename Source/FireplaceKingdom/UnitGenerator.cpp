// Fill out your copyright notice in the Description page of Project Settings.

#include "FireplaceKingdom.h"
#include "UnitGenerator.h"
#include "QueuedTile.h"
#include "TileStruct.h"
#include "Engine/DataTable.h"
#include <EngineGlobals.h>
#include "UnrealNetwork.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>


// Sets default values
AUnitGenerator::AUnitGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
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

/*void AUnitGenerator::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}*/

void AUnitGenerator::AddTile(FName ID)
{

	FTileStruct Row = *DataTable->FindRow<FTileStruct>(ID, TEXT(""));
	UQueuedTile* _Tile = NewObject<UQueuedTile>();
	_Tile->TileData = Row;
	_Tile->CalculateUnitsLeftToSpawn();
	Tiles.Add(_Tile);
}

// Called every frame by server(actor doesn't tick itself)
void AUnitGenerator::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (HasAuthority()) {
		SpawnTimer -= DeltaTime;
		if (SpawnTimer <= 0) {
			if (Tiles.Num() > 0 && pTile == NULL) {
				pTile = Tiles.Pop();
				SetSpawnTimer();
			}
			else if (pTile != NULL) {
				SetSpawnTimer();
				GenerateUnit();
			}
			else {

			}
		}
	}
}

void AUnitGenerator::GenerateUnit()
{

	UWorld* const World = GetWorld(); // get a reference to the world
	if (World) {
		// if world exists
		for (int i = 0; i < pTile->TileData.UnitsPerSpawn; i++) {
			AUnit* Unit = World->SpawnActor<AUnit>(pTile->TileData.Unit, GetActorLocation(), GetActorRotation());
			Unit->Lane = Lane;
			Unit->SetActorLocation(GetRandomNearbyLocation());
		}
		pTile->DeductSpawnedUnits();
		if (pTile->UnitsLeftToSpawn <= 0) {
			pTile = NULL;
		}
	}
}

FVector AUnitGenerator::GetRandomNearbyLocation()
{
	FVector Location = GetActorLocation();
	return Location + FVector(rand() % 30, rand() % 30, 0);
}

void AUnitGenerator::SetSpawnTimer()
{
	if (pTile != NULL) {
		SpawnTimer = pTile->TileData.SpawnDelay;
	}
}
