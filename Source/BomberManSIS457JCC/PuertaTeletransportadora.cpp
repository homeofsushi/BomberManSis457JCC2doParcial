// Fill out your copyright notice in the Description page of Project Settings.


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
    PrimaryActorTick.bCanEverTick = false;

    // 1. Creamos y configuramos el componente de colisi�n (UBoxComponent)
    CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    RootComponent = CollisionComp;
    CollisionComp->InitBoxExtent(FVector(50.f, 50.f, 100.f));
    CollisionComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    // 2. Creamos y configuramos el componente de malla (UStaticMeshComponent)
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshPuerta"));
    MeshComp->SetupAttachment(RootComponent);

    // Cargamos un mesh predeterminado (por ejemplo, un cubo estirado)
    static ConstructorHelpers::FObjectFinder<UStaticMesh> PuertaMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
    if (PuertaMesh.Succeeded())
    {
        MeshComp->SetStaticMesh(PuertaMesh.Object);
        MeshComp->SetRelativeScale3D(FVector(1.f, 0.2f, 2.f));
    }
    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); // La colisi�n la maneja CollisionComp

    // Cargamos un material gen�rico (por ejemplo, agua u otro)
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> PuertaMaterial(TEXT("Material'/Game/StarterContent/Materials/M_Water_Ocean.M_Water_Ocean'"));
    if (PuertaMaterial.Succeeded())
    {
        MeshComp->SetMaterial(0, PuertaMaterial.Object);
    }

    // Cargamos un efecto de part�culas para el teletransporte
    static ConstructorHelpers::FObjectFinder<UParticleSystem> TeleportFX(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Sparks.P_Sparks'"));
    if (TeleportFX.Succeeded())
    {
        TeleportEffect = TeleportFX.Object;
    }
    else
    {
        TeleportEffect = nullptr;
    }
}

void APuertaTeletransportadora::InitializeBlock()
{
    // 1. Vincular el evento de overlap con nuestro handler
    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APuertaTeletransportadora::OnOverlapBegin);

    // 2. Inicializar la lista de PuertasTeletransportadoras si a�n no est� seteada.
    //    (En muchos casos, llamaremos a SetPuertasTeletransportadoras(...) desde el Builder
    //     justo despu�s de spawnear todas las puertas, para que cada puerta conozca a las dem�s).
}


void APuertaTeletransportadora::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    // 1. Verificamos que el overlap sea con un ACharacter
    ACharacter* Personaje = Cast<ACharacter>(OtherActor);
    if (!Personaje) return;

    // 2. Evitar teletransportar al mismo personaje demasiado r�pido
    static const FName CooldownTag = TEXT("TeleportedRecently");
    if (Personaje->Tags.Contains(CooldownTag)) return;

    // 3. Ejecutar teletransporte
    TeletransportarPersonaje(Personaje);
}

void APuertaTeletransportadora::TeletransportarPersonaje(ACharacter* Personaje)
{
    if (!Personaje) return;

    static const FName CooldownTag = TEXT("TeleportedRecently");

    // 1. Agregar un tag para evitar recursividad inmediata
    if (!Personaje->Tags.Contains(CooldownTag))
    {
        Personaje->Tags.Add(CooldownTag);

        // 2. Crear lista de puertas posibles (sin incluir esta misma)
        TArray<APuertaTeletransportadora*> OtrasPuertas = PuertasTeletransportadoras;
        OtrasPuertas.Remove(this);

        if (OtrasPuertas.Num() > 0)
        {
            // 3. Elegir �ndice aleatorio
            int32 IndiceAleatorio = FMath::RandRange(0, OtrasPuertas.Num() - 1);
            APuertaTeletransportadora* PuertaDestino = OtrasPuertas[IndiceAleatorio];
            FVector Destino = PuertaDestino->GetActorLocation();

            // 4. Reproducir efecto de part�culas en la puerta destino
            if (TeleportEffect && GetWorld())
            {
                UGameplayStatics::SpawnEmitterAtLocation(
                    GetWorld(),
                    TeleportEffect,
                    Destino,
                    FRotator::ZeroRotator,
                    true
                );
            }

            // 5. Mover al personaje a la ubicaci�n de la puerta destino
            Personaje->SetActorLocation(Destino);
        }

        // 6. Programar la eliminaci�n del tag despu�s de 0.5 segundos
        FTimerHandle TimerHandle;
        if (GetWorld())
        {
            const FName CooldownTagCopy = CooldownTag; // Crear una copia local de la variable est�tica
            GetWorld()->GetTimerManager().SetTimer(
                TimerHandle,
                [Personaje, CooldownTagCopy]()
                {
                    Personaje->Tags.Remove(CooldownTagCopy);
                },
                0.5f,
                false
            );
        }

    }
}