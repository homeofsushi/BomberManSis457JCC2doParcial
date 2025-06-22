// Fill out your copyright notice in the Description page of Project Settings.


#include "BombaParticula.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "BloqueBase.h" 
#include "Particles/ParticleSystem.h"


ABombaParticula::ABombaParticula()
{
    PrimaryActorTick.bCanEverTick = true;
    // Crear y asignar la malla
    UStaticMeshComponent* Malla = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaBomba"));
    RootComponent = Malla;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> EsferaMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
    if (EsferaMesh.Succeeded())
    {
        Malla->SetStaticMesh(EsferaMesh.Object);
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> OroMat(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Steel.M_Metal_Steel'"));
    if (OroMat.Succeeded())
    {
        Malla->SetMaterial(0, OroMat.Object);
    }
    static ConstructorHelpers::FObjectFinder<UParticleSystem> Particulas(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
    if (Particulas.Succeeded())
    {
        ParticulasExplosion = Particulas.Object;
    }
    Movimiento = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movimiento"));
    Movimiento->InitialSpeed = 600.f;
    Movimiento->MaxSpeed = 600.f;
    Movimiento->bRotationFollowsVelocity = true;
    Movimiento->ProjectileGravityScale = 0.f;
    Danio = 30;
    RadioExplosion = 300.f;
}

void ABombaParticula::BeginPlay()
{
    Super::BeginPlay();
    OnActorHit.AddDynamic(this, &ABombaParticula::OnHit);
}

void ABombaParticula::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    Explota();
}

void ABombaParticula::Explota()
{
    if (ParticulasExplosion)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticulasExplosion, GetActorLocation());
    }

    // Encuentra bloques dentro del radio
    TArray<AActor*> BloquesAfectados;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABloqueBase::StaticClass(), BloquesAfectados);
    // Crear un composite para los bloques afectados
    ABloqueComposite* Grupo = GetWorld()->SpawnActor<ABloqueComposite>();

    for (AActor* Bloque : BloquesAfectados)
    {
        if (FVector::Dist(Bloque->GetActorLocation(), GetActorLocation()) <= RadioExplosion)
        {
            IBloqueComponent* BloqueComp = Cast<IBloqueComponent>(Bloque);
            if (BloqueComp)
            {
                Grupo->AgregarHijo(TScriptInterface<IBloqueComponent>(Bloque));
            }
        }
    }

    // Aplicar daño a todos los hijos del composite
    Grupo->RecibirDanio(Danio);

    // Si el grupo solo se usa para la explosión, puedes destruirlo después
    Grupo->Destroy();

    Destroy();
}


