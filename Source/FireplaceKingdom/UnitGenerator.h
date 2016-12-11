// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tile.h"
#include "ActiveTile.h"
#include "LaneSpline.h"
#include "UnitGenerator.generated.h"

UCLASS()
class FIREPLACEKINGDOM_API AUnitGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnitGenerator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void GenerateUnit();
	void SetSpawnTimer();
	void AddTile(FName ID);
	FVector GetRandomNearbyLocation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	TArray<FName> DebugTiles;


	TArray<ActiveTile> Tiles;
	ActiveTile *pTile;
	ActiveTile Tile;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
	ALaneSpline* Lane;

	float SpawnTimer;
	float SpawnDelay;

	UPROPERTY(EditAnywhere)
	UDataTable* DataTable;
};
