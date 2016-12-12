// Fill out your copyright notice in the Description page of Project Settings.

#include "FireplaceKingdom.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Unit.h"


// Sets default values
AUnit::AUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	MovementCooldown = 0;
	Health = 100.f;
}

void AUnit::AttackTarget_Implementation(AUnit *Target)
{
	Target->Health -= rand() % 4;
}

bool AUnit::AttackTarget_Validate(AUnit *Target)
{
	return true;
}

// Called every frame
void AUnit::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (Role == ROLE_Authority) {
		if (Health <= 0)
			Destroy();

		MovementCooldown -= DeltaTime;

		if (MovementCooldown <= 0 && Lane && Lane->Spline != NULL) {
			MovementCooldown = 0.1f;
			SplineDistance += 100;
			FVector Location = Lane->Spline->GetWorldLocationAtDistanceAlongSpline(SplineDistance);

			UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
			float const Distance = FVector::Dist(Location, GetActorLocation());
			// We need to issue move command only if far enough in order for walk animation to play correctly
			if (NavSys && (Distance > 0.0f))
			{
				NavSys->SimpleMoveToLocation(GetController(), Location);
			}

		}
	}
}

