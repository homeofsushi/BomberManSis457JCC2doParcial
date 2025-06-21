// Fill out your copyright notice in the Description page of Project Settings.


#include "BombaGrande.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
ABombaGrande::ABombaGrande()
{
    PrimaryActorTick.bCanEverTick = true;
    UStaticMeshComponent* Malla = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaBomba"));
    RootComponent = Malla;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> EsferaMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
    if (EsferaMesh.Succeeded())
    {
        Malla->SetStaticMesh(EsferaMesh.Object);
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> OroMat(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold'"));
    if (OroMat.Succeeded())
    {
        Malla->SetMaterial(0, OroMat.Object);
    }
    Movimiento = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movimiento"));
    Movimiento->InitialSpeed = 600.f;
    Movimiento->MaxSpeed = 600.f;
    Movimiento->bRotationFollowsVelocity = true;
    Movimiento->ProjectileGravityScale = 0.f;
    EscalaObjetivo = 2.0f;
}

void ABombaGrande::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FVector EscalaActual = GetActorScale3D();
    if (EscalaActual.X < EscalaObjetivo)
    {
        EscalaActual += FVector(DeltaTime, DeltaTime, DeltaTime);
        SetActorScale3D(EscalaActual);
    }
    else
    {
        Explota();
    }
}

void ABombaGrande::Explota()
{
    // Lógica de explosión aquí
    Destroy();
}
