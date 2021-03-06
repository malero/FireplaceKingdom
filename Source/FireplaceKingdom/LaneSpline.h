// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "LaneSpline.generated.h"

UCLASS()
class FIREPLACEKINGDOM_API ALaneSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaneSpline();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/**Spline component*/
	UPROPERTY(BlueprintReadWrite)
	USplineComponent* Spline;
};
