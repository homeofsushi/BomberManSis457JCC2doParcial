#include "ALaberintoDirector.h"
#include "ULaberintoBuilderDefault.h"
#include "EnemigoTerrestre.h"
#include "EnemigoAcuatico.h"
#include "EnemigoAereo.h"

AALaberintoDirector::AALaberintoDirector()
{
    PrimaryActorTick.bCanEverTick = false;
    Builder = nullptr;
    LaberintoConstruido = nullptr;
}

void AALaberintoDirector::BeginPlay()
{
    Super::BeginPlay();

    // Instancia el builder
    Builder = NewObject<ULaberintoBuilderDefault>(this);

    // Construye el laberinto usando el builder
    ConstruirLaberinto(Builder);

    // Obtén el laberinto generado
    LaberintoConstruido = Builder->ObtenerLaberinto();

    // Puedes hacer algo con LaberintoConstruido aquí si lo necesitas
    // 1. Recolectar posiciones vacías
    TArray<FIntPoint> PosicionesVacias;
    for (int i = 0; i < LaberintoConstruido->MatrizBloques.Num(); ++i)
    {
        for (int j = 0; j < LaberintoConstruido->MatrizBloques[i].Num(); ++j)
        {
            if (LaberintoConstruido->MatrizBloques[i][j] == nullptr)
            {
                PosicionesVacias.Add(FIntPoint(i, j));
            }
        }
    }

    // 2. Barajar posiciones vacías para aleatoriedad
    for (int32 i = 0; i < PosicionesVacias.Num(); ++i)
    {
        int32 SwapIdx = FMath::RandRange(i, PosicionesVacias.Num() - 1);
        PosicionesVacias.Swap(i, SwapIdx);
    }

    float EspaciadoX = 100.f;
    float EspaciadoY = 100.f;
    FVector LaberintoOffset = FVector(-1800.f, -1400.f, 0.f);

    UWorld* World = LaberintoConstruido->GetWorld();
    FActorSpawnParameters Params;

    TArray<TSubclassOf<AEnemigoBase>> TiposEnemigos = {
        AEnemigoTerrestre::StaticClass(),
        AEnemigoAereo::StaticClass(),
        AEnemigoAcuatico::StaticClass()
    };

    // 3. Spawnear un enemigo de cada tipo en una posición vacía diferente
    for (int32 k = 0; k < TiposEnemigos.Num() && k < PosicionesVacias.Num(); ++k)
    {
        FIntPoint Celda = PosicionesVacias[k];
        float x = LaberintoOffset.X + Celda.Y * EspaciadoX;
        float y = LaberintoOffset.Y + Celda.X * EspaciadoY;
        float z = 0.f;
        FVector SpawnLocation(x, y, z);

        if (World)
        {
            World->SpawnActor<AEnemigoBase>(TiposEnemigos[k], SpawnLocation, FRotator::ZeroRotator, Params);
        }
    }
}

void AALaberintoDirector::ConstruirLaberinto(ULaberintoBuilder* InBuilder)
{
    if (InBuilder)
    {
        InBuilder->ConstruirLaberinto();
    }
}

void AALaberintoDirector::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}



