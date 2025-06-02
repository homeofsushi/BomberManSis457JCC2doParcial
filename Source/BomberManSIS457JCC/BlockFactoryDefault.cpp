// BlockFactoryDefault.cpp
#include "BlockFactoryDefault.h"
#include "BloqueMadera.h"
#include "BloqueLadrillo.h"
#include "BloqueAcero.h"
#include "Coin.h"
#include "PuertaTeletransportadora.h"
#include "Engine/World.h"

/**
 * Implementación del Factory Method
 */
ABloqueBase* UBlockFactoryDefault::FabricarBloque_Implementation(
    ETipoBloque Tipo,
    const FTransform& SpawnTransform,
    AActor* Owner
) const
{
    if (!Owner)
    {
        return nullptr;
    }

    UWorld* World = Owner->GetWorld();
    if (!World)
    {
        return nullptr;
    }

    // Aquí elegimos la clase concreta a spawnear
    TSubclassOf<ABloqueBase> ClaseConcreta = nullptr;

    switch (Tipo)
    {
    case ETipoBloque::Madera:
        ClaseConcreta = ABloqueMadera::StaticClass();
        break;

    case ETipoBloque::Ladrillo:
        ClaseConcreta = ABloqueLadrillo::StaticClass();
        break;

    case ETipoBloque::Acero:
        ClaseConcreta = ABloqueAcero::StaticClass();
        break;

    case ETipoBloque::Coin:
        ClaseConcreta = ACoin::StaticClass();
        break;

    case ETipoBloque::Puerta:
        ClaseConcreta = APuertaTeletransportadora::StaticClass();
        break;

    default:
        return nullptr;
    }

    // Spawneamos el actor en la world
    ABloqueBase* NuevoBloque = World->SpawnActor<ABloqueBase>(ClaseConcreta, SpawnTransform);
    if (NuevoBloque)
    {
        // Llamamos a InitializeBlock() para que el bloque configure su mesh, colisión, etc.
        NuevoBloque->InitializeBlock();
    }
    return NuevoBloque;
}

