// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "Team.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ETeamEnum : uint8
{
	T_Neutral 	UMETA(DisplayName = "Neutral"),
	T_Santa 	UMETA(DisplayName = "Santa"),
	T_Krampus	UMETA(DisplayName = "Krampus")
};


/**
 * 
 */
UCLASS()
class FIREPLACEKINGDOM_API UTeam : public UObject
{
	GENERATED_BODY()
	
	
	
	
};
