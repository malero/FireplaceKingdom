// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "Team.h"
#include "UnitGenerator.h"
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

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Team")
	ETeamEnum GetTeam();

	void AddPoints(uint32 _Points);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player")
	int32 GetPoints();

	UPROPERTY()
	TArray<AUnitGenerator*> Generators;

	void FindGenerators();

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Build Phase")
	void BuyUnit(FName Name, int32 GeneratorPosition);
	void BuyUnit_Implementation(FName Name, int32 GeneratorPosition);
	bool BuyUnit_Validate(FName Name, int32 GeneratorPosition);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Build Phase")
	void SetReady();
	void SetReady_Implementation();
	bool SetReady_Validate();

	UFUNCTION(BlueprintCallable, Category = "Build Phase")
	bool GetReady();

	/* Kind of weird function, but I don't want clients to be able to pass a bool into SetReady() */
	void UnsetReady();

private:
	// The team of the player
	UPROPERTY(Replicated)
	ETeamEnum Team;

	// Points to buy units
	UPROPERTY(Replicated)
	int32 Points;

	bool Ready;
};
