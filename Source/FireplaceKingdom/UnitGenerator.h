// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tile.h"
#include "QueuedTile.h"
#include "LaneSpline.h"
#include "Team.h"
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

	void AddTile(FName ID);
	FVector GetRandomNearbyLocation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	TArray<FName> DebugTiles;

	UPROPERTY()
	TArray<UQueuedTile*> Tiles;

	UPROPERTY()
	UQueuedTile* Tile;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
	ALaneSpline* Lane;

	UPROPERTY(EditAnywhere, Category = "Generator")
	UDataTable* DataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
	ETeamEnum Team;

protected:
	FTimerHandle SpawnTimerHandle;

	float TimerDelay;

	void SetSpawnTimer();

	void SpawnUnits();
};
