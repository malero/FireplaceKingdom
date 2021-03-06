// Fill out your copyright notice in the Description page of Project Settings.

#include "FireplaceKingdom.h"
#include "UnitGenerator.h"
#include "QueuedTile.h"
#include "TileStruct.h"
#include "FireplaceKingdomGameMode.h"
#include "MyGameStateBase.h"
#include "Engine/DataTable.h"
#include "UnrealNetwork.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>


// Sets default values
AUnitGenerator::AUnitGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

// Called when the game starts or when spawned
void AUnitGenerator::BeginPlay()
{
	Super::BeginPlay();

	if (Role == ROLE_Authority)
	{
		// Make UTileComponents from DebugTiles(if any are present)
		for (int i = 0; i < DebugTiles.Num(); i++) {
			AddTile(DebugTiles[i]);
		}
		// Set initial spawn delay
		TimerDelay = 1.f;
		SetSpawnTimer();
	}
}

/*void AUnitGenerator::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}*/

FTileStruct* AUnitGenerator::GetRow(FName ID)
{
	return DataTable->FindRow<FTileStruct>(ID, TEXT(""));
}

void AUnitGenerator::AddTile(FName ID)
{
	FTileStruct* Row = GetRow(ID);
	if (Row)
	{
		UQueuedTile * _Tile = NewObject<UQueuedTile>();
		_Tile->SetTileData(Row);
		Tiles.Add(_Tile);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Row Not Found"));
	}
}

// Called every frame
void AUnitGenerator::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

bool AUnitGenerator::IsActionMode()
{
	AFireplaceKingdomGameMode* GameMode = Cast<AFireplaceKingdomGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode) {
		AMyGameStateBase* State = GameMode->GetGameState();
		if(State)
			return State->CurrentState == EGameState::T_Action;
	}
	return false;
}

void AUnitGenerator::SpawnUnits()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("SpawnUnitsCall"));
	if (Role == ROLE_Authority)
	{
		UWorld* const World = GetWorld(); // get a reference to the world
		if (World && Tile != nullptr && IsActionMode())
		{
			// if world exists
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString("Units To Spawn: ") + FString::FromInt(Tile->UnitsPerSpawn));
			for (int i = 0; i < Tile->UnitsPerSpawn; i++)
			{
				AUnit* Unit = World->SpawnActor<AUnit>(Tile->Unit, GetActorLocation(), GetActorRotation(), SpawnParams);
				Unit->Lane = Lane;
				Unit->SetActorLocation(GetRandomNearbyLocation());
				Unit->Team = Team;
				
				// Set unit properties
				Unit->Health = Tile->Health;
				Unit->AttackMin = Tile->AttackMin;
				Unit->AttackMax = Tile->AttackMax;
				Unit->AttackDistance = Tile->AttackDistance;
				Unit->VisionDistance = Tile->VisionDistance;
				Unit->SetMovementSpeed(Tile->MovementSpeed);

				Tile->DeductSpawnedUnit();
			}
			if (Tile->GetUnitsLeftToSpawn() <= 0)
			{
				Tile = nullptr;
				TimerDelay = 1.f;
			}
		}

		// If the current tile is done spawning, let's see if there is another tile in the queue and grab it
		if (Tiles.Num() > 0 && Tile == nullptr)
		{
			Tile = Tiles.Pop();
			TimerDelay = Tile->SpawnDelay;
		}
		SetSpawnTimer();
	}
}

FVector AUnitGenerator::GetRandomNearbyLocation()
{
	FVector Location = GetActorLocation();
	return Location + FVector(rand() % 30, rand() % 30, 0);
}

void AUnitGenerator::SetSpawnTimer()
{
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AUnitGenerator::SpawnUnits, TimerDelay, false);
}
