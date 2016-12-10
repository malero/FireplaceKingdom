// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "LaneSpline.h"
#include "Unit.generated.h"

UCLASS()
class FIREPLACEKINGDOM_API AUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnit();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	ALaneSpline* Lane;
};