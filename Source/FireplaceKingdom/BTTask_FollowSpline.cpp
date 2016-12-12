// Fill out your copyright notice in the Description page of Project Settings.

#include "FireplaceKingdom.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Unit.h"
#include "ElfAI.h"
#include "BTTask_FollowSpline.h"

EBTNodeResult::Type UBTTask_FollowSpline::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AElfAI *ElfAI = Cast<AElfAI>(OwnerComp.GetAIOwner());
	AUnit *Elf = Cast<AUnit>(ElfAI->GetPawn());

	if (Elf)
	{
		Elf->MoveAlongSpline();
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}


