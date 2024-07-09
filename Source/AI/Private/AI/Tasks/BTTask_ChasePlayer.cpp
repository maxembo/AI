// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_ChasePlayer.h"

#include "AI/NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer(FObjectInitializer const& ObjectInitializer)
: UBTTask_BlackboardBase(ObjectInitializer)
{
	NodeName = "Chase Player";
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = Cast<ANPC_AIController>(OwnerComp.GetAIOwner());
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if(!Blackboard || !Controller) return EBTNodeResult::Failed;

	auto const PlayerLocation = Blackboard->GetValueAsVector(GetSelectedBlackboardKey());
	
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, PlayerLocation);
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		
	return EBTNodeResult::Succeeded;
}
