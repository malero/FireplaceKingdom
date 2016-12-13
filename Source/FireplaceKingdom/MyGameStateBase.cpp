// Fill out your copyright notice in the Description page of Project Settings.

#include "FireplaceKingdom.h"
#include "UnrealNetwork.h"
#include "Unit.h"
#include "MyPlayerState.h"
#include "Team.h"
#include "MyGameStateBase.h"

void AMyGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMyGameStateBase, CurrentState);
	DOREPLIFETIME(AMyGameStateBase, PhaseTimer);
}

float AMyGameStateBase::GetPhaseTimer() {
	return PhaseTimer;
}

void AMyGameStateBase::Tick(float DeltaSeconds)
{
	if (Role != ROLE_Authority)
		return;

	if (PhaseTimer >= 0)
		PhaseTimer -= DeltaSeconds;

	if (CurrentState == EGameState::T_Over && PhaseTimer <= 0)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "/Game/Levels/MainMenu");
	}
	else
	{

		if (CurrentState == EGameState::T_Build) {
			if (PhaseTimer <= 0 || ArePlayersReady()) {
				MakePlayersNotReady();
				CurrentState = EGameState::T_Action;
				PhaseTimer = 25.f;
				Round += 1;

				// If we're playing single player, let's add some units
				if (PlayerArray.Num() == 1) {
					SetupSinglePlayerRound();
				}
			}
		}
		else if (CurrentState == EGameState::T_Action)
		{
			if (PhaseTimer <= 0) {
				// Count the number of elves remaining
				int32 UnitsLeft = 0;
				for (TActorIterator<AUnit> StartItr(GetWorld()); StartItr; ++StartItr)
				{
					UnitsLeft += 1;
				}
				if (UnitsLeft == 2) {
					PhaseTimer = 60.f;
					CurrentState = EGameState::T_Build;
				}
				else if (UnitsLeft == 1)
				{
					CurrentState = EGameState::T_Over;
				}
			}
		}
	}

	// Start the final countdown
	if (IsGameOver() && CurrentState != EGameState::T_Over) {
		PhaseTimer = 3;
		CurrentState = EGameState::T_Over;
	}
}

FString AMyGameStateBase::GetStateLabel()
{
	if (CurrentState == EGameState::T_Action)
	{
		return FString("Battle Phase");
	}
	else if (CurrentState == EGameState::T_Build)
	{
		return FString("Build Phase");
	}
	else
	{
		return FString("Game Over");
	}
}

bool AMyGameStateBase::IsGameOver()
{
	uint8 LeadersLeft = 0;
	for (TActorIterator<AUnit> StartItr(GetWorld()); StartItr; ++StartItr)
	{
		if(StartItr->Leader)
			LeadersLeft += 1;
	}
	return LeadersLeft < 2;
}

bool AMyGameStateBase::ArePlayersReady()
{
	if (PlayerArray.Num() == 1) {
		AMyPlayerState* PlayerState = Cast<AMyPlayerState>(PlayerArray[0]);

		if (!PlayerState)
			return false;

		if (PlayerState->GetReady())
			return true;
	}
	else
	{
		AMyPlayerState* PlayerState1 = Cast<AMyPlayerState>(PlayerArray[0]);
		AMyPlayerState* PlayerState2 = Cast<AMyPlayerState>(PlayerArray[1]);

		if (PlayerState1 && PlayerState2 && PlayerState1->GetReady() && PlayerState2->GetReady())
			return true;
	}
	return false;
}

void AMyGameStateBase::MakePlayersNotReady()
{
	if (PlayerArray.Num() > 0) {
		AMyPlayerState* PlayerState = Cast<AMyPlayerState>(PlayerArray[0]);
		if (PlayerState)
			PlayerState->UnsetReady();
	}

	if (PlayerArray.Num() > 1) {
		AMyPlayerState* PlayerState = Cast<AMyPlayerState>(PlayerArray[1]);
		if (PlayerState)
			PlayerState->UnsetReady();
	}

}


/**
 * Single Player Functionality
  * Copied from PlayerState...
*/

/* Find any generators that are not the play characters */
void AMyGameStateBase::FindGenerators()
{
	Generators.Empty();

	if (PlayerArray.Num() < 1)
		return;

	AMyPlayerState* PlayerState = Cast<AMyPlayerState>(PlayerArray[0]);

	if (!PlayerState)
		return;

	for (TActorIterator<AUnitGenerator> StartItr(GetWorld()); StartItr; ++StartItr)
	{
		if (StartItr->Team != PlayerState->GetTeam())
			Generators.Add(*StartItr);
	}
}

void AMyGameStateBase::SetupSinglePlayerRound()
{
	FindGenerators();
	int8 UnitsToPurchase = FMath::RandRange(Round * 1, Round * 3) + Round * 2;
	for (int8 i = 0; i < UnitsToPurchase; i++)
	{
		AUnitGenerator* Generator = Generators[FMath::RandRange(0, Generators.Num() - 1)];
		int8 UnitToSpawn = FMath::RandRange(0, 2);
		if (UnitToSpawn == 0)
		{
			Generator->AddTile(FName("Brute"));
		}
		else if (UnitToSpawn == 1)
		{
			Generator->AddTile(FName("Grunts"));
		}
		else {
			Generator->AddTile(FName("Warriors"));
		}
	}
}