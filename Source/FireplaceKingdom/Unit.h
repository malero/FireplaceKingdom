// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "LaneSpline.h"
#include "Team.h"
#include "Unit.generated.h"

UCLASS()
class FIREPLACEKINGDOM_API AUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnit();

	UPROPERTY(EditAnywhere, Category = "Behavior")
	class UBehaviorTree *UnitBehavior;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	ALaneSpline* Lane;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Binding")
	USkeletalMeshComponent* UnitMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	ETeamEnum Team;

	UFUNCTION(BlueprintCallable, category = "Unit")
	float GetHealth();

	void SetMovementSpeed(float Speed);
	void MoveAlongSpline();

	float SplineDistance;
	float MovementCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	bool Leader;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Unit")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	float AttackMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	float AttackMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	float AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	float VisionDistance; // How far can this unit see and spot enemeies/other PoIs?

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	float MovementSpeed;

	UFUNCTION(Server, Reliable, WithValidation)
	void AttackTarget(AUnit *Target);
	void AttackTarget_Implementation(AUnit *Target);
	bool AttackTarget_Validate(AUnit *Target);
};
