// Fill out your copyright notice in the Description page of Project Settings.

#include "FireplaceKingdom.h"
#include "MyPlayerState.h"
#include "UnrealNetwork.h"
#include "FireplaceKingdomGameMode.h"
#include "MyGameStateBase.h"
#include "Team.h"


void AMyPlayerState::SetTeam(ETeamEnum _Team)
{
	Team = _Team;
}

ETeamEnum AMyPlayerState::GetTeam()
{
	return Team;
}

void AMyPlayerState::AddPoints(uint32 _Points)
{
	Points += _Points;
}

int32 AMyPlayerState::GetPoints()
{
	return Points;
}

void AMyPlayerState::FindGenerators()
{
	Generators.Empty();
	for (TActorIterator<AUnitGenerator> StartItr(GetWorld()); StartItr; ++StartItr)
	{
		if (StartItr->Team == GetTeam())
			Generators.Add(*StartItr);
	}
}

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMyPlayerState, Team);
	DOREPLIFETIME(AMyPlayerState, Points);
}

void AMyPlayerState::BuyUnit_Implementation(FName Name, int32 GeneratorPosition)
{
	if (Ready)
		return;

	if (Generators.Num() < GeneratorPosition)
		return;

	AUnitGenerator* Generator = Generators[GeneratorPosition];
	FTileStruct* Row = Generator->GetRow(Name);

	if (!Row)
		return;

	if (Points < Row->Price)
		return;

	AFireplaceKingdomGameMode* GameMode = Cast<AFireplaceKingdomGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode) {
		AMyGameStateBase* State = GameMode->GetGameState();
		if (State && State->CurrentState != EGameState::T_Build)
			return;
	}

	Points -= Row->Price;
	Generator->AddTile(Name);
}

bool AMyPlayerState::BuyUnit_Validate(FName Name, int32 GeneratorPosition)
{
	return true;
}

void AMyPlayerState::SetReady_Implementation()
{
	AFireplaceKingdomGameMode* GameMode = Cast<AFireplaceKingdomGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode) {
		AMyGameStateBase* State = GameMode->GetGameState();
		if (!Ready && State && State->CurrentState == EGameState::T_Build)
		{
			Ready = true;
			AddPoints(int(State->GetPhaseTimer()) * 10);
		}
	}
}

bool AMyPlayerState::SetReady_Validate()
{
	return true;
}

bool AMyPlayerState::GetReady()
{
	return Ready;
}

void AMyPlayerState::UnsetReady()
{
	Ready = false;
}
