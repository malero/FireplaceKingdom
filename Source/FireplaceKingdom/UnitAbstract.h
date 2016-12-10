// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "LaneSpline.h"
#include "UnitAbstract.generated.h"

UCLASS()
class FIREPLACEKINGDOM_API AUnitAbstract : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnitAbstract();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		ALaneSpline* Lane;
	
};