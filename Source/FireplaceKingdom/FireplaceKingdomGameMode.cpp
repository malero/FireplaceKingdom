// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "FireplaceKingdom.h"
#include "FireplaceKingdomGameMode.h"
#include "FireplaceKingdomPlayerController.h"
#include "FireplaceKingdomCharacter.h"

AFireplaceKingdomGameMode::AFireplaceKingdomGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AFireplaceKingdomPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}