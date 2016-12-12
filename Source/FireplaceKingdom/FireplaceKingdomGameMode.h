// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "FireplaceKingdomGameMode.generated.h"

UCLASS(minimalapi)
class AFireplaceKingdomGameMode : public AGameModeBase
{
	GENERATED_BODY()


	void PostLogin(APlayerController * NewPlayer) override;
	AActor* ChoosePlayerStart(AController* Player);
public:
	AFireplaceKingdomGameMode();
	bool ShouldSpawnAtStartSpot(AController* Player) override { return false; };
};
