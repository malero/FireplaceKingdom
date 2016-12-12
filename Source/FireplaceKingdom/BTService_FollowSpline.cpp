// Fill out your copyright notice in the Description page of Project Settings.

#include "FireplaceKingdom.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Unit.h"
#include "ElfAI.h"
#include "BTService_FollowSpline.h"


UBTService_FollowSpline::UBTService_FollowSpline()
{
	bCreateNodeInstance = true;
}

void UBTService_FollowSpline::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AElfAI *ElfAI = Cast<AElfAI>(OwnerComp.GetAIOwner());
	AUnit *Elf = Cast<AUnit>(ElfAI->GetPawn());

	if (ElfAI && Elf)
	{
		// Check to see if there are any enemies in sight
		AUnit *Enemy = nullptr;
		for (TActorIterator<AUnit> StartItr(GetWorld()); StartItr; ++StartItr)
		{
			float Distance = StartItr->GetDistanceTo(Elf);
			if (StartItr->Team != Elf->Team && Distance <= Elf->VisionDistance) {
				if (Enemy && Enemy->GetDistanceTo(Elf) > Distance) {
					Enemy = *StartItr;
				}

				if (!Enemy)
					Enemy = *StartItr;
			}
		}

		if (Enemy)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(ElfAI->EnemyKeyID, Enemy);
			//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Enemy is here!!");
		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "No Enemy :(");
		}
	}
}
