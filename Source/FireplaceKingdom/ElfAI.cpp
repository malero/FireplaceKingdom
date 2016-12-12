// Fill out your copyright notice in the Description page of Project Settings.

#include "FireplaceKingdom.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Unit.h"
#include "ElfAI.h"


AElfAI::AElfAI()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	BehaviorComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComponent"));
}

void AElfAI::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AUnit *Char = Cast<AUnit>(InPawn);

	if (Char && Char->UnitBehavior)
	{
		BlackboardComponent->InitializeBlackboard(*Char->UnitBehavior->BlackboardAsset);

		// The Key on the blackboard component
		EnemyKeyID = BlackboardComponent->GetKeyID("Target");

		BehaviorComponent->StartTree(*Char->UnitBehavior);
	}
}