// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Unit.h"
#include "TileStruct.generated.h"

/**
 * 
 */
USTRUCT()
struct FTileStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AUnit> Unit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 UnitsToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 UnitsPerSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SpawnDelay;
};