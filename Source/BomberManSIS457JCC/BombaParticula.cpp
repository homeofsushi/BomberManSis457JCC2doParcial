// Fill out your copyright notice in the Description page of Project Settings.


#include "BombaParticula.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystem.h"
#include "UObject/ConstructorHelpers.h"

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
    Destroy();
}


