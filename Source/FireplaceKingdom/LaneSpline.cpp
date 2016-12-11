// Fill out your copyright notice in the Description page of Project Settings.

#include "FireplaceKingdom.h"
#include "LaneSpline.h"


// Sets default values
ALaneSpline::ALaneSpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// USplineComponent* Spline = CreateDefaultSubobject<USplineComponent>(TEXT("RootComponent"));
	// RootComponent = Spline;

}

// Called when the game starts or when spawned
void ALaneSpline::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALaneSpline::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
