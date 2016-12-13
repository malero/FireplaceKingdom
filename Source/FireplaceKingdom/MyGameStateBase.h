// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameStateBase.h"
#include "UnitGenerator.h"
#include "MyGameStateBase.generated.h"


UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EGameState : uint8
{
	T_Build 	UMETA(DisplayName = "Build Phase"),
	T_Action 	UMETA(DisplayName = "Action Phase"),
	T_Over		UMETA(DisplayName = "Game Over")
};


/**
 * 
 */
UCLASS()
class FIREPLACEKINGDOM_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated)
	EGameState CurrentState;

	UFUNCTION(BlueprintCallable, Category = "Game State")
	FString GetStateLabel();

	void Tick(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "Game State")
	float GetPhaseTimer();

	UPROPERTY()
	TArray<AUnitGenerator*> Generators;

	void FindGenerators();

private:
	UPROPERTY(Replicated)
	float PhaseTimer = 60.f;

	void SetupSinglePlayerRound();

	bool IsGameOver();

	bool ArePlayersReady();
	void MakePlayersNotReady();

	int32 Round = 0;
};
