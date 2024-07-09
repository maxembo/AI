// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_FindPathPoint.h"
#include "AI/NPC.h"
#include "AI/NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPathPoint::UBTTask_FindPathPoint(FObjectInitializer const& ObjectInitializer)
: UBTTask_BlackboardBase(ObjectInitializer)
{
	NodeName = "Find Path Point";
}

EBTNodeResult::Type UBTTask_FindPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = Cast<ANPC_AIController>(OwnerComp.GetAIOwner());
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if(!Blackboard || ! Controller) return EBTNodeResult::Failed;

	const auto Index = Blackboard->GetValueAsInt(GetSelectedBlackboardKey());
	const auto Npc = Cast<ANPC>(Controller->GetPawn());
	if(!Npc) return EBTNodeResult::Failed;
	
	const auto Point = Npc->GetPatrolPath()->GetPatrolPoint(Index);
	const auto GlobalPoint = Npc->GetPatrolPath()->GetActorTransform().TransformPosition(Point);
	Blackboard->SetValueAsVector(PatrolPathVectorKey.SelectedKeyName, GlobalPoint);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
