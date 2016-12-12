// Fill out your copyright notice in the Description page of Project Settings.

#include "FireplaceKingdom.h"
#include "MyPlayerState.h"
#include "UnrealNetwork.h"
#include "Team.h"


void AMyPlayerState::SetTeam(ETeamEnum _Team)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ETeamEnum"), true);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, EnumPtr->GetEnumName((int32)_Team));
	Team = _Team;
}

ETeamEnum AMyPlayerState::GetTeam()
{
	return Team;
}

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMyPlayerState, Team);
}