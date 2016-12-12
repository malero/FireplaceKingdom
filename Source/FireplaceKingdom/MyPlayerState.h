// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "Team.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FIREPLACEKINGDOM_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	void SetTeam(ETeamEnum _Team);

private:
	// The team of the player
	ETeamEnum Team;
};
