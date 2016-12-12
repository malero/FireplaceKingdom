// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "ElfAI.generated.h"

/**
 * 
 */
UCLASS()
class FIREPLACEKINGDOM_API AElfAI : public AAIController
{
	GENERATED_BODY()

		UPROPERTY(transient)
		class UBlackboardComponent *BlackboardComponent;

	UPROPERTY(transient)
		class UBehaviorTreeComponent *BehaviorComponent;

public:
	AElfAI();

	virtual void Possess(APawn* InPawn) override;
	
	uint8 EnemyKeyID;
};
