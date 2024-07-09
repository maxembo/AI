// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Tasks/BTTask_FindRandomLocation.h"
#include "NavigationSystem.h"
#include "AI/NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer)
: UBTTask_BlackboardBase(ObjectInitializer)
{
	NodeName = "Find Random Location In NavMesh";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Controller = Cast<ANPC_AIController>(OwnerComp.GetAIOwner());
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	if(!BlackBoard || !Controller) return EBTNodeResult::Failed;
	
	const auto Npc = Controller->GetPawn();
	if(!Npc) return EBTNodeResult::Failed;

	const auto Origin = Npc->GetActorLocation();

	const auto NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if(!NavSystem) return EBTNodeResult::Failed;

	FNavLocation NavLocation;
	const auto bCompleted = NavSystem->GetRandomPointInNavigableRadius(Origin, Radius,NavLocation);
	if(!bCompleted) return EBTNodeResult::Failed;

	BlackBoard->SetValueAsVector(GetSelectedBlackboardKey(),NavLocation.Location);
	return EBTNodeResult::Succeeded;
}
