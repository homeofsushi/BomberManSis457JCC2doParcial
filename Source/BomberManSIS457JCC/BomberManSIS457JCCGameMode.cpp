// Copyright Epic Games, Inc. All Rights Reserved.

#include "BomberManSIS457JCCGameMode.h"
#include "BomberManSIS457JCCCharacter.h"
#include "BlockFactoryDefault.h"
#include "PuertaTeletransportadora.h"
#include "ALaberintoDirector.h"
#include "UObject/ConstructorHelpers.h"

ABomberManSIS457JCCGameMode::ABomberManSIS457JCCGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ABomberManSIS457JCCGameMode::BeginPlay()
{
    Super::BeginPlay();

    UWorld* World = GetWorld();
    if (World)
    {
        FActorSpawnParameters Params;
        AALaberintoDirector* Director = World->SpawnActor<AALaberintoDirector>(AALaberintoDirector::StaticClass(), Params);
        // El director hará todo en su BeginPlay
    }
}
