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

}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnit::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (Lane->Spline != NULL) {
		SplineDistance += DeltaTime * 100;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Distance: " + FString::FromInt (int(SplineDistance)));
		FRotator Rotation = Lane->Spline->GetWorldRotationAtDistanceAlongSpline(SplineDistance);
		FVector Location = Lane->Spline->GetWorldLocationAtDistanceAlongSpline(SplineDistance);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Location: " + FString::FromInt(Location.X) + ", " + FString::FromInt(Location.Y));
		SetActorRotation(Rotation);
		SetActorLocation(Location);
	}
}

// Called to bind functionality to input
void AUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

