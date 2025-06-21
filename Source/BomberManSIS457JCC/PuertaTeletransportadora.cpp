// Source\BomberManSIS457JCC\PuertaTeletransportadora.cpp
#include "PuertaTeletransportadora.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"

APuertaTeletransportadora::APuertaTeletransportadora()
{
    // Crear y adjuntar componentes
    CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
    RootComponent = CollisionComp;

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(RootComponent);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
    if (MeshAsset.Succeeded())
    {
        MeshComp->SetStaticMesh(MeshAsset.Object);
    }

    // Tama�o de la caja de colisi�n
    CollisionComp->SetBoxExtent(FVector(50.f, 50.f, 100.f));

    // PERFIL DE COLISI�N: debe ser OverlapAllDynamic para detectar overlaps
    CollisionComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    // Hacer visible la colisi�n en el editor para depuraci�n
    CollisionComp->bHiddenInGame = false;
    CollisionComp->SetVisibility(true);

    // Enlazar el evento de overlap
    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APuertaTeletransportadora::OnOverlapBegin);
}

void APuertaTeletransportadora::InitializeBlock()
{
    // Aqu� puedes inicializar la malla, materiales, etc.
}

void APuertaTeletransportadora::SetPuertasTeletransportadoras(const TArray<APuertaTeletransportadora*>& TodasPuertas)
{
    PuertasTeletransportadoras = TodasPuertas;
}

void APuertaTeletransportadora::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("Overlap detectado con: %s"), *OtherActor->GetName());
    ACharacter* Personaje = Cast<ACharacter>(OtherActor);
    if (Personaje)
    {
        TeletransportarPersonaje(Personaje);
    }
}

void APuertaTeletransportadora::TeletransportarPersonaje(ACharacter* Personaje)
{
    if (PuertasTeletransportadoras.Num() <= 1) return;

    // Elegir una puerta aleatoria distinta de esta
    APuertaTeletransportadora* Destino = nullptr;
    do
    {
        int32 Index = FMath::RandRange(0, PuertasTeletransportadoras.Num() - 1);
        Destino = PuertasTeletransportadoras[Index];
    } while (Destino == this);

    if (Destino)
    {
        // Teletransportar al personaje a la ubicaci�n de la puerta destino
        Personaje->SetActorLocation(Destino->GetActorLocation());
    }
}