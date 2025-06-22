// Fill out your copyright notice in the Description page of Project Settings.


#include "JuegoFacadeActor.h"
#include "ALaberintoDirector.h"
#include "ULaberintoBuilderDefault.h"
#include "BombaFactoryConcreta.h"
#include "Engine/World.h"

// Constructor
AJuegoFacadeActor::AJuegoFacadeActor()
{
    PrimaryActorTick.bCanEverTick = true;
    Director = nullptr;
    Builder = nullptr;
    BombFactory = nullptr;
}

void AJuegoFacadeActor::BeginPlay()
{
    Super::BeginPlay();

    UWorld* World = GetWorld();
    if (World)
    {
        Builder = NewObject<ULaberintoBuilderDefault>(World);
        Director = World->SpawnActor<AALaberintoDirector>();
        BombFactory = NewObject<UBombaFactoryConcreta>();
    }
}

void AJuegoFacadeActor::ConstruirLaberinto()
{
    if (Director && Builder)
    {
        Director->ConstruirLaberinto(Builder);
    }
}

void AJuegoFacadeActor::SpawnBomb(EBombType Tipo, const FVector& Location, const FRotator& Rotation)
{
    if (BombFactory)
    {
        BombFactory->CrearBomba(GetWorld(), Location, Rotation, Tipo);
    }
}



