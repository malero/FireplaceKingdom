// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "MyGameStateBase.h"
#include "FireplaceKingdomGameMode.generated.h"

UCLASS(minimalapi)
class AFireplaceKingdomGameMode : public AGameModeBase
{
	GENERATED_BODY()

	void Tick(float DeltaSeconds);
	void PostLogin(APlayerController * NewPlayer) override;
	AActor* ChoosePlayerStart_Implementation(AController* Player);
	float PhaseTimer;
public:
	AFireplaceKingdomGameMode();

	UFUNCTION(BlueprintCallable, Category = "Game State")
	AMyGameStateBase* GetGameState();

	bool ShouldSpawnAtStartSpot(AController* Player) override { return false; };
};
