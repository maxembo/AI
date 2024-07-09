// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/BTService_IsPlayerMeleeRange.h"
#include "AI/NPC.h"
#include "AI/NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_IsPlayerMeleeRange::UBTService_IsPlayerMeleeRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player Melee Range");
}

void UBTService_IsPlayerMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = Cast<ANPC_AIController>(OwnerComp.GetAIOwner());
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	const auto Npc = Cast<ANPC>(Controller->GetPawn());
	if (!Controller || !Npc || !Blackboard) return;

	const auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if(!Player) return;

	Blackboard->SetValueAsBool(GetSelectedBlackboardKey(), Npc->GetDistanceTo(Player) <= MeleeRange);
}
