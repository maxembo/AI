// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_IncrementPathIndex.h"

#include "AI/NPC.h"
#include "AI/NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_IncrementPathIndex::UBTTask_IncrementPathIndex(FObjectInitializer const& ObjectInitializer)
	: UBTTask_BlackboardBase(ObjectInitializer)
{
	NodeName = "Increment Path Index";
}

EBTNodeResult::Type UBTTask_IncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = Cast<ANPC_AIController>(OwnerComp.GetAIOwner());
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard || !Controller) return EBTNodeResult::Failed;

	const auto Npc = Cast<ANPC>(Controller->GetPawn());
	if(!Npc) return EBTNodeResult::Failed;

	const auto NoOfPoints = Npc->GetPatrolPath()->Num();
	const auto MinIndex = 0;
	const auto MaxIndex = NoOfPoints - 1;
	auto Index = Blackboard->GetValueAsInt(GetSelectedBlackboardKey());

	if(!bDirection) return EBTNodeResult::Failed;

	if(Index >= MaxIndex && Direction == EDirectionType::Forward)
		Direction = EDirectionType::Reverse;
	else if(Index == MinIndex && Direction == EDirectionType::Reverse)
		Direction = EDirectionType::Forward;

	Blackboard->SetValueAsInt(GetSelectedBlackboardKey(),
		(Direction == EDirectionType::Forward ? ++Index : --Index) % NoOfPoints);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
