#include "ALaberintoDirector.h"
#include "ULaberintoBuilderDefault.h"

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

    // Obt�n el laberinto generado
    LaberintoConstruido = Builder->ObtenerLaberinto();

    // Puedes hacer algo con LaberintoConstruido aqu� si lo necesitas
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



