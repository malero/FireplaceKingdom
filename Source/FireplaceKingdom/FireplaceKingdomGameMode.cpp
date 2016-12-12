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

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

AFireplaceKingdomGameMode::AFireplaceKingdomGameMode()
{
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

void AFireplaceKingdomGameMode::PostLogin(APlayerController * NewPlayer) {
	Super::PostLogin(NewPlayer);
	if (NewPlayer)
	{
		AMyPlayerState* PlayerState = Cast<AMyPlayerState>(NewPlayer->PlayerState);
		int32 PlayerCount = GameState->PlayerArray.Num();
		if (GameState && PlayerState)
		{
			if (PlayerCount == 1)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Setting Player to Team Santa"));
				PlayerState->SetTeam(ETeamEnum::T_Santa);
			}
			else if(PlayerCount == 2)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Setting Player to Team Krampus"));
				PlayerState->SetTeam(ETeamEnum::T_Krampus);
			}
			else
			{
				// Kill the new player!!!! There isn't a third team. psh...
				NewPlayer->Destroy();
			}
		}
	}
}

AActor* AFireplaceKingdomGameMode::ChoosePlayerStart(AController* Player)
{
	if (Player)
	{
		AMyPlayerState* PlayerState = Cast<AMyPlayerState>(Player->PlayerState);
		if (PlayerState)
		{
			TArray<AMyPlayerStart*> StartingAreas;
			for (TActorIterator<AMyPlayerStart> StartItr(GetWorld()); StartItr; ++StartItr)
			{
				if (StartItr->Team == PlayerState->GetTeam())
					StartingAreas.Add(*StartItr);
			}
			return StartingAreas[FMath::RandRange(0, StartingAreas.Num() - 1)];
		}
	}
	return NULL;
}
