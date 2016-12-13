// Fill out your copyright notice in the Description page of Project Settings.

#include "FireplaceKingdom.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "UnrealNetwork.h"
#include "FireplaceKingdomGameMode.h"
#include "MyPlayerState.h"
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
}

void AUnit::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AUnit, Health);
}

void AUnit::AttackTarget_Implementation(AUnit *Target)
{
	float Damage = FMath::RandRange(AttackMin, AttackMax);
	AFireplaceKingdomGameMode* GameMode = Cast<AFireplaceKingdomGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		for (int32 i = 0; i < GameMode->GameState->PlayerArray.Num(); i++)
		{
			AMyPlayerState* PlayerState = Cast<AMyPlayerState>(GameMode->GameState->PlayerArray[i]);
			if (PlayerState && PlayerState->GetTeam() == Team && Damage >= AttackMax - 1)
			{
				PlayerState->AddPoints(1);
			}
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("No game mode"));
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString("Damage: ") + FString::SanitizeFloat(Damage) + FString(" Target Health:" + FString::SanitizeFloat(Target->Health)));
	Target->Health -= Damage;
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
	}
}

void AUnit::MoveAlongSpline()
{
	if (Role == ROLE_Authority && Lane) {
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

void AUnit::SetMovementSpeed(float Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

float AUnit::GetHealth()
{
	return Health;
}
