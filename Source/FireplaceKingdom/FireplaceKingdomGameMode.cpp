// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "FireplaceKingdom.h"
#include "EngineUtils.h"
#include "FireplaceKingdomGameMode.h"
#include "FireplaceKingdomPlayerController.h"
#include "FireplaceKingdomCharacter.h"
#include "MyPlayerState.h"
#include "MyGameStateBase.h"
#include "Team.h"
#include "MyPlayerStart.h"
#include "Unit.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

AFireplaceKingdomGameMode::AFireplaceKingdomGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	// set default Controller to CameraPawnController blueprint
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDownCPP/CameraPawnController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/CameraPawn"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Set default HUD class
	static ConstructorHelpers::FObjectFinder<UClass> HUDFinder(TEXT("WidgetBlueprint'/Game/HUD/BPGameHUD.BPGameHUD_C'"));
	if (HUDFinder.Object) {
		HUDClass = HUDFinder.Object;
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString("Cannot find HUD"));
	}

	PlayerStateClass = AMyPlayerState::StaticClass();

	GameStateClass = AMyGameStateBase::StaticClass();
}

void AFireplaceKingdomGameMode::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	GetGameState()->Tick(DeltaSeconds);
}

AMyGameStateBase* AFireplaceKingdomGameMode::GetGameState()
{
	AMyGameStateBase* State = Cast<AMyGameStateBase>(GameState);
	if (State)
		return State;
	return NULL;
}

void AFireplaceKingdomGameMode::PostLogin(APlayerController * NewPlayer) {
	Super::PostLogin(NewPlayer);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Setting Teams!"));
	AMyPlayerState* PlayerState = Cast<AMyPlayerState>(NewPlayer->PlayerState);
	PlayerState->AddPoints(500);
}

AActor* AFireplaceKingdomGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	if (Player)
	{
		AMyPlayerState* PlayerState = Cast<AMyPlayerState>(Player->PlayerState);
		if (PlayerState)
		{
			int32 PlayerCount = GameState->PlayerArray.Num();
			if (GameState && PlayerState)
			{

				// Weird place to do this, but no time!
				PlayerState->FindGenerators();

				if (PlayerCount == 1)
				{
					PlayerState->SetTeam(ETeamEnum::T_Santa);
				}
				else if (PlayerCount == 2)
				{
					PlayerState->SetTeam(ETeamEnum::T_Krampus);
					// There are two players, Start the game!!!
					GetGameState()->CurrentState = EGameState::T_Build;
				}
			}


			TArray<AMyPlayerStart*> StartingAreas;
			for (TActorIterator<AMyPlayerStart> StartItr(GetWorld()); StartItr; ++StartItr)
			{
				if (StartItr->Team == PlayerState->GetTeam())
					StartingAreas.Add(*StartItr);
			}

			if (StartingAreas.Num() > 0) {
				return StartingAreas[FMath::RandRange(0, StartingAreas.Num() - 1)];
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("No Spawn"));
	}
	return NULL;
}
