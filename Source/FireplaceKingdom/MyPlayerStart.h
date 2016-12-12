// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerStart.h"
#include "Team.h"
#include "MyPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class FIREPLACEKINGDOM_API AMyPlayerStart : public APlayerStart
{
	GENERATED_BODY()
	
public:
	// The team of the starting area
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
	ETeamEnum Team;
	
};
