// Fill out your copyright notice in the Description page of Project Settings.

#include "FireplaceKingdom.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Unit.h"
#include "ElfAI.h"
#include "BTService_CheckForElves.h"

UBTService_CheckForElves::UBTService_CheckForElves()
{
	bCreateNodeInstance = true;
}

void UBTService_CheckForElves::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AElfAI *ElfAI = Cast<AElfAI>(OwnerComp.GetAIOwner());
	AUnit *Elf = Cast<AUnit>(ElfAI->GetControlledPawn());

	if (ElfAI && Elf)
	{
		// Check to see if there are any enemies in sight
		AUnit *Enemy = Cast<AUnit>(GetWorld()->GetFirstPlayerController()->GetPawn());
		TArray<AUnit*> Enemies;
		for (TActorIterator<AUnit> StartItr(GetWorld()); StartItr; ++StartItr)
		{
			if (StartItr->Team != Elf->Team && StartItr->GetDistanceTo(Elf) < 500.f)
				Enemies.Add(*StartItr);
		}

		if (Enemies.Num() > 0)
			Enemy = Enemies[0];

		if (Enemy)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(ElfAI->EnemyKeyID, Enemy);
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Enemy is here!!");
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "No Enemy :(");
		}
	}
}
