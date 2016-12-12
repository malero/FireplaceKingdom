// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "BTService_FollowSpline.generated.h"

/**
 * 
 */
UCLASS()
class FIREPLACEKINGDOM_API UBTService_FollowSpline : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_FollowSpline();
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
