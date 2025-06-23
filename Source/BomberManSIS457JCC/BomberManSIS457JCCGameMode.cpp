// Copyright Epic Games, Inc. All Rights Reserved.

#include "BomberManSIS457JCCGameMode.h"
#include "BomberManSIS457JCCCharacter.h"
#include "BlockFactoryDefault.h"
#include "PuertaTeletransportadora.h"
#include "ALaberintoDirector.h"
#include "JuegoFacadeActor.h"
#include "EnemigoBase.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ABomberManSIS457JCCGameMode::ABomberManSIS457JCCGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	Facade = nullptr;
}

void ABomberManSIS457JCCGameMode::BeginPlay()
{
    Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{
		Facade = World->SpawnActor<AJuegoFacadeActor>();
		if (Facade)
		{
			Facade->ConstruirLaberinto();
		}
	}
	OrdenarAccionEnemigos();
}
void ABomberManSIS457JCCGameMode::SpawnBomb(EBombType Tipo, const FVector& Location, const FRotator& Rotation)
{
	if (Facade)
	{
		Facade->SpawnBomb(Tipo, Location, Rotation);
	}
}
void ABomberManSIS457JCCGameMode::OrdenarAccionEnemigos()
{
	if (!Facade) return;

	// Obtener todos los enemigos en el mundo
	TArray<AActor*> Enemigos;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemigoBase::StaticClass(), Enemigos);

	for (AActor* Actor : Enemigos)
	{
		AEnemigoBase* Enemigo = Cast<AEnemigoBase>(Actor);
		if (Enemigo)
		{
			Enemigo->BuscarJugador();
			// Decide si mover o atacar según tu lógica
			float Dist = FVector::Dist(Enemigo->GetActorLocation(), Enemigo->Objetivo ? Enemigo->Objetivo->GetActorLocation() : FVector::ZeroVector);
			if (Dist < 250.0f)
				Facade->OrdenarAtacarEnemigo(Enemigo);
			else
				Facade->OrdenarMoverEnemigo(Enemigo);
		}
	}
}