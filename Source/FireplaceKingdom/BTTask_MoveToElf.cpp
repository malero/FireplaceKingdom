// Fill out your copyright notice in the Description page of Project Settings.

#include "FireplaceKingdom.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Unit.h"
#include "ElfAI.h"
#include "BTTask_MoveToElf.h"


EBTNodeResult::Type UBTTask_MoveToElf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AElfAI *ElfAI = Cast<AElfAI>(OwnerComp.GetAIOwner());
	AUnit *Elf = Cast<AUnit>(ElfAI->GetPawn());
	AUnit *Enemy = Cast<AUnit>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(ElfAI->EnemyKeyID));

	if (Enemy && Elf)
	{
		
		if (Elf->GetDistanceTo(Enemy) > Elf->AttackDistance)
		{
			ElfAI->MoveToActor(Enemy, 5.f, true, true, true, 0, true);
			return EBTNodeResult::Succeeded;
		}
		// We're within attacking range, let's killl!
		// Failing will tell behavior tree to move on to the next task
		return EBTNodeResult::Failed;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}
