// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_FindPlayerLocation.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UBTTask_FindPlayerLocation::UBTTask_FindPlayerLocation(FObjectInitializer const& ObjectInitializer)
: UBTTask_BlackboardBase(ObjectInitializer)
{
	NodeName = "Find Player Location in NavMesh";
}

EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	if (!BlackBoard || !Player) return EBTNodeResult::Failed;

	const auto PlayerLocation = Player->GetActorLocation();

	const auto NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSystem) return EBTNodeResult::Failed;

	if (bSearchRandom)
	{
		FNavLocation NavLocation;
		const auto bCompleted = NavSystem->GetRandomPointInNavigableRadius(PlayerLocation, Radius, NavLocation);
		if (!bCompleted) return EBTNodeResult::Failed;

		BlackBoard->SetValueAsVector(GetSelectedBlackboardKey(), NavLocation.Location);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		BlackBoard->SetValueAsVector(GetSelectedBlackboardKey(), PlayerLocation);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	return EBTNodeResult::Succeeded;
}
