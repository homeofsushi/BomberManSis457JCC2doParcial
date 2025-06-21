// Fill out your copyright notice in the Description page of Project Settings.


#include "BombaFactoryConcreta.h"
#include "Bomba.h"
#include "BombaSimple.h"
#include "BombaGrande.h"
#include "BombaParticula.h"

ABomba* UBombaFactoryConcreta::CrearBomba(UWorld* World, const FVector& Location, const FRotator& Rotation, EBombType Tipo)
{
    switch (Tipo)
    {
    case EBombType::Simple:
        return World->SpawnActor<ABombaSimple>(Location, Rotation);
    case EBombType::Creciente:
        return World->SpawnActor<ABombaGrande>(Location, Rotation);
    case EBombType::Textura:
        return World->SpawnActor<ABombaParticula>(Location, Rotation);
    default:
        return nullptr;
    }
}