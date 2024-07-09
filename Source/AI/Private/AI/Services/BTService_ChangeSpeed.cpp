// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/BTService_ChangeSpeed.h"
#include "AIController.h"
#include "AI/NPC.h"
#include "GameFramework/CharacterMovementComponent.h"

UMyBTService_ChangeSpeed::UMyBTService_ChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Change Speed");
}

void UMyBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Npc = Cast<ANPC>(Controller->GetPawn());
	if(!Controller || !Npc) return;

	Npc->GetCharacterMovement()->MaxWalkSpeed = Speed;
}
