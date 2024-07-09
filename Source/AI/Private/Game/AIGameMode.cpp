// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game/AIGameMode.h"
#include "Character/AICharacter.h"
#include "UObject/ConstructorHelpers.h"

AAIGameMode::AAIGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
